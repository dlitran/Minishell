/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/19 23:48:05 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	gt_dollar(char *dlr, t_data *d, t_qte *qte)
{
	int	len;
	int	i;

	i = 0;
	if (ft_strlen(dlr) == 0)
	{
		qte->new = add_in_front2("$", qte, 0, 1);
		return ;
	}
	while (d->env[i])
	{
		len = 0;
		while (d->env[i][len] && d->env[i][len] != 61)
			len++;
		if (ft_strncmp(dlr, d->env[i], len) == 0)
		{
			qte->new = add_in_front2(d->env[i], qte, len + 1,
					ft_strlen(d->env[i]) - len - 1);
			return ;
		}
		i++;
	}
	return ;
}

static char	*add_dollar(t_qte *qte, int *i, int start, t_data *d)
{
	while (qte->arg[*i] != 34 && qte->arg[*i])
	{
		if (qte->arg[*i] == 36)
		{
			change_dlr_sub(qte, &start, i, d);
			if (qte->flag_err == 1)
				return (NULL);
		}
		else
			*i += 1;
	}
	qte->new = add_in_front(qte, start, *i - start);
	return (qte->new);
}

char	*del_simple_quotes(t_qte *qte, int *i, int start_a, t_data *d)
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

static void	get_quotes(t_qte *qte, t_data *d)
{
	int		i;
	int		start;

	qte->flag_err = 0;
	i = 0;
	start = 0;
	while (qte->arg[i])
	{
		if (qte->arg[i] == 39 || qte->arg[i] == 34)
			is_qte_sub(qte, &start, &i, d);
		/*else if (qte->arg[i] == 36)
			is_dlr_sub(qte, &start, &i, d);*/
		else
			i++;
		if (qte->flag_err == 1)
			return ;
	}
	qte->new = add_in_front(qte, start, i - start);
	return ;
}

char	*ft_substr_mnsh(char const *s, unsigned int srt, size_t len, t_data *d)
{
	t_qte	*qte;
	char	*str;

	qte = malloc(sizeof(t_qte) * 1);
	if (!qte)
		return (NULL);
	if (srt > ft_strlen(s))
		srt = ft_strlen(s);
	if (len > ft_strlen(s + srt))
		len = ft_strlen(s + srt);
	if (ft_strlen(s) < srt)
		len = 0;
	qte->arg = ft_calloc(sizeof(char), len + 1);
	if (!qte->arg)
		return (NULL);
	ft_strlcpy(qte->arg, s + srt, len + 1);
	qte->new = NULL;
	get_quotes(qte, d);
	str = ft_strdup(qte->new);
	d->flag_err = qte->flag_err;
	if (!str && d->flag_err == 0)
		d->flag_err = 2;
	free_qte(qte);
	return (str);
}
