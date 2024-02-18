/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/18 21:06:49 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static char	*gt_dollar(char *dlr, char *new, t_data *d)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (ft_strlen(dlr) == 1)
	{
		new = add_in_front("$", new, 0, 1);
		return (new);
	}
	while (d->env[i])
	{
		while (d->env[i][len] != 61)
			len++;
		if ((int)ft_strlen(dlr) == len && ft_strncmp(dlr, d->env[i], i))
		{
			new = add_in_front(d->env[i], new, len, ft_strlen(d->env[i]) - len);
			return (new);
		}
		i++;
	}
	return (new);
}

static char	*add_dollar(t_qte *qte, int *i, int start, t_data *d)
{
	char	*sub;

	sub = NULL;
	while (qte->arg[*i] != 34)
	{
		if (qte->arg[*i] == 36)
		{
			qte->new = add_in_front(qte->arg, qte->new, start, *i - start);
			if (!qte->new)
				return (NULL);
			*i += 1;
			start = *i;
			*i = ft_go_end_dollar(qte->arg, *i);
			sub = ft_substr(qte->arg, start, *i - start);
			if (!sub)
				return (NULL);
			qte->new = gt_dollar(sub, qte->new, d);
			if (!qte->new)
				return (NULL);
		}
		else
			*i += 1;
	}
	qte->new = add_in_front(qte->arg, qte->new, start, *i - start);
	return (qte->new);
}

static char	*del_simple_quotes(t_qte *qte, int *i, int start_a, t_data *d)
{
	int	start;

	(void)start_a;
	*i += 1;
	start = *i;
	if (qte->arg[*i - 1] == 39)
	{
		*i = ft_go_next_quote(qte->arg, *i, qte->arg[*i - 1]);
		*i += 1;
		if (*i - 1 == start)
			return (qte->new);
		else
			qte->new = add_in_front(qte->arg, qte->new, start, *i - start - 1);
	}
	else
		qte->new = add_dollar(qte, i, start, d);
	return (qte->new);
}

static char	*get_quotes(char *str, size_t len, t_data *d)
{
	(void)len;
	(void)d;
	int		i;
	int		start;
	t_qte	qte;

	qte.new = NULL;
	qte.arg = str;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (i > 0 && !qte.new)
				return (NULL);
			if (str[i + 1] != str[i])
			{
				qte.new = del_simple_quotes(&qte, &i, start, d);
				if (!qte.new)
					return (NULL);
			}
			else
				i += 2;
			start = i;
		}
		else
			i++;
	}
	qte.new = add_in_front(qte.arg, qte.new, start, i - start);
	return (qte.new);
}

char	*ft_substr_mnsh(char const *s, unsigned int start, size_t len, t_data *d)
{
	char	*str;
	char	*new;

	str = NULL;
	new = NULL;
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (ft_strlen(s) < start)
		len = 0;
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	new = get_quotes(str, len, d);
	free(str);
	return (new);
}
