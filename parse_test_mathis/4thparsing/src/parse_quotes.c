/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:34:57 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 21:38:22 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*add_in_front(char *arg, char *new, int start, int len)
{
	char	*dup_arg;
	char	*dup_new;

	if (len > 0 && new)
	{
		dup_arg = ft_substr(arg, start, len);
		if (!dup_arg)
			return (return_error_quotes(new));
		dup_new = ft_strdup(new);
		if (!dup_new)
		{
			free(dup_arg);
			return (return_error_quotes(new));
		}
		free(new);
		new = ft_strjoin(dup_new, dup_arg);
		free(dup_arg);
		free(dup_new);
	}
	else if (len > 0)
		new = ft_substr(arg, start, len);
	return (new);
}

char	*replace_quote(t_qte *q, int *i, t_data *d)
{
	q->startrq = *i + 1;
	*i = ft_nxt_qte(q->arg, *i + 1, q->arg[*i]);
	if (q->arg[*i] == 39)
		q->new = add_in_front(q->arg, q->new, q->startrq, *i - q->startrq);
	else
	{
		if (is_dollar(q->arg, q->startrq))
		{	
			q->s = q->startrq;
			q->new = isrt_dlr_in_arg(q, q->startrq, d, NULL);
		}
		else
			q->new = add_in_front(q->arg, q->new, q->startrq, *i - q->startrq);
	}
	*i += 1;
	return (q->new);
}

char	*which_quote(t_qte *q, char *arg, int i, t_data *d)
{
	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			if (i > 0)
			{
				q->new = add_in_front(q->arg, q->new, q->startwq,
						i - q->startwq);
				if (!q->new)
					return (NULL);
			}
			q->new = replace_quote(q, &i, d);
			q->startwq = i;
			if (!q->new)
				return (NULL);
		}
		else
			i++;
	}
	q->new = add_in_front(q->arg, q->new, q->startwq, i - q->startwq);
	return (q->new);
}

char	*is_there_quote(char *arg, int nba, t_data *d, int i)
{
	char	*str;
	t_qte	*q;

	q = ft_calloc(sizeof(t_qte), 1);
	if (!q)
		return (NULL);
	q->nba = nba;
	q->new = NULL;
	arg = ft_dollar_sign(arg, 0, 0, d);
	q->arg = arg;
	while (arg && arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			str = which_quote(q, arg, 0, d);
			free(q);
			free(arg);
			return (str);
		}
		i++;
	}
	free(q);
	return (arg);
}

void	parse_quotes(t_data *d, int j)
{
	t_cmd	*first;

	first = d->cmd;
	while (d->cmd)
	{
		while (d->cmd->arg[j])
		{
			d->cmd->arg[j] = is_there_quote(d->cmd->arg[j], j, d, 0);
			if (!d->cmd->arg[j])
			{
				while (d->cmd->arg[j + 1])
				{
					free(d->cmd->arg[j + 1]);
					j++;
				}
				return ;
			}
			j++;
		}
		free(d->cmd->exe);
		d->cmd->exe = d->cmd->arg[0];
		d->cmd = d->cmd->next;
	}
	d->cmd = first;
}
