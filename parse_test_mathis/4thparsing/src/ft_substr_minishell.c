/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/19 17:56:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static char	*gt_dollar(char *dlr, char *new, t_data *d, t_qte *qte)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (ft_strlen(dlr) == 1)
	{
		new = add_in_front2("$", qte, 0, 1);
		return (new);
	}
	while (d->env[i])
	{
		while (d->env[i][len] && d->env[i][len] != 61)
			len++;
		if ((int)ft_strlen(dlr) - 1 == len && ft_strncmp(dlr, d->env[i], i))
		{
			new = add_in_front2(d->env[i], qte, len - 1, ft_strlen(d->env[i]) - len - 1);
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
	while (qte->arg[*i] != 34 && qte->arg[*i])
	{
		if (qte->arg[*i] == 36)
		{
			qte->new = add_in_front(qte, start, *i - start);
			if (qte->flag_err == 1)
				return (NULL);
			start = *i;
			*i = ft_go_end_dollar(qte->arg, *i + 1);
			sub = ft_substr(qte->arg, start, *i - start);
			if (!sub)
				return (NULL);
			write(1, "rwqe\n", 5);
			qte->new = gt_dollar(sub, qte->new, d, qte);
			write(1, "rwqe\n", 5);
			free(sub);
			if (qte->flag_err == 1)
				return (NULL);
			write(1, "rwqe\n", 5);
			*i += 1;
			start = *i;
		}
		else
			*i += 1;
	}
	qte->new = add_in_front(qte, start, *i - start);
	write(1, "rrre\n", 5);
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
			qte->new = add_in_front(qte, start, *i - start - 1);
	}
	else
		qte->new = add_dollar(qte, i, start, d);
	return (qte->new);
}

static char	*get_quotes(t_qte *qte, t_data *d)
{
	int		i;
	int		start;

	qte->flag_err = 0;
	i = 0;
	start = 0;
	while (qte->arg[i])
	{
		if (qte->arg[i] == 39 || qte->arg[i] == 34)
		{
			qte->new = add_in_front(qte, start, i - start);
			printf("1er add_in_front%s\n", qte->new);
			if (qte->flag_err == 1)
				return (NULL);
			if (qte->arg[i + 1] != qte->arg[i])
			{
				qte->new = del_simple_quotes(qte, &i, start, d);
				printf("2nd add_in_front%s\n", qte->new);
				if (qte->flag_err == 1)
					return (NULL);
			}
			else
				i += 2;
			start = i;
		}
		else
		{
			write(1, "12345\n", 6);
			i++;
		}
	}
	//printf("avant la fin de get_quotes%s\n", qte->new);
	write(1, "12345\n", 6);
	qte->new = add_in_front(qte, start, i - start);
	write(1, "54321\n", 6);
	return (qte->new);
}

char	*ft_substr_mnsh(char const *s, unsigned int start, size_t len, t_data *d)
{
	t_qte	*qte;
	char	*str;

	qte = malloc(sizeof(t_qte) * 1);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (ft_strlen(s) < start)
		len = 0;
	qte->arg = ft_calloc(sizeof(char), len + 1);
	if (!qte->arg)
		return (NULL);
	ft_strlcpy(qte->arg, s + start, len + 1);
	//qte->arg[len + 1] = '\0';
	qte->new = NULL;
	qte->new = get_quotes(qte, d);
	if (!qte->new)
		return (NULL);
	free(qte->arg);
	str = ft_strdup(qte->new);
	free(qte->new);
	free(qte);
	printf("apres le strdup: %s\n", str);
	return (str);
}
