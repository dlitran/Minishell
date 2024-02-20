/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_in_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:25:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/20 20:18:53 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*return_error_quotes(char *new, int nb)
{
	if (new)
		free(new);
	perror("error allocating memory for quote parsing\n");
	nb_error = nb;
	return (NULL);
}

int	find_next_space(char *input, int i)
{
	while (input[i] && (input[i] != ' ' && input[i] != '\t'
			&& input[i] != '\n' && input[i] != '\f'
			&& input[i] != '\r' && input[i] != '\v'
			&& input[i] != 34 && input[i] != 39
			&& input[i] != '$'))
		i++;
	return (i);
}
/*
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
			new = add_in_front(d->env[j], new, len + 1,
					ft_strlen(d->env[j]) - len);
			free(dlr);
			return (new);
		}
		j++;
	}
	free(dlr);
	return (new);
}

char	*isrt_dlr_in_arg(t_qte *q, int i, t_data *d, char *dlr)
{
	while (q->arg[i])
	{
		if (q->arg[i] == '$')
		{
			if (i - q->s > 0)
			{
				q->new = add_in_front(q->arg, q->new, q->s, i - q->s);
				if (!q->new)
					return (return_error_quotes(NULL));
			}
			dlr = ft_substr(q->arg, i + 1, find_next_space(q->arg,
						i + 1) - i - 1);
			if (!dlr)
				return (return_error_quotes(q->new));
			q->new = insert_dlr(q->new, dlr, d);
			if (!q->new)
				return (return_error_quotes(NULL));
			i = find_next_space(q->arg, i + 1);
			q->s = i;
		}
		else
			i++;
	}
	return (q->new);
}*/
