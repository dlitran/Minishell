/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_in_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:25:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 12:56:01 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*return_error_quotes(char *new)
{
	if (new)
		free(new);
	perror("error allocating memory for quote parsing");
	return (NULL);
}

int	find_next_space(char *input, int i)
{
	while (input[i] && (input[i] != ' ' && input[i] != '\t'
		&& input[i] != '\n' && input[i] != '\f' && input[i] != '\r'
		&& input[i] != '\v'))
		i++;
	return (i);
}

char	*insert_dlr(char *new, char *dlr, t_data *d)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(dlr);
	while (d->env[j])
	{
		if (strncmp(d->env[j], dlr, len) == 0)
		{
			new = add_in_front(d->env[j], new, len, ft_strlen(d->env[j] - len));
			return new;
		}
		j++;
	}
	return (new);
}

char	*isrt_dlr_in_arg(t_qte *q, int i, t_data *d, char *dlr)
{
	write(1, "gogogo", 6);
	q->startins = i;
	while (q->arg[i] && q->arg[i] != 34)
	{
		if (q->arg[i] == '$' && !(i == q->startins && q->nba == 0))
		{
			q->new = add_in_front(q->arg, q->new, q->startins, i - q->startins);
			if (!q->new)
				return (return_error_quotes(NULL));
			dlr = ft_substr(q->arg, i + 1, find_next_space(q->arg, i) - i + 1);
			if (!dlr)
				return (return_error_quotes(q->new));
			q->new = insert_dlr(q->new, dlr, d);
			if (!q->new)
				return (return_error_quotes(NULL));
			i = find_next_space(q->arg, i);
			q->startins = i;
		}
		else
			i++;
	}
	q->new = add_in_front(q->arg, q->new, q->startins, i - q->startins);
	return (q->new);
}
