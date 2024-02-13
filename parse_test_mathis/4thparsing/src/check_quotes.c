/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:23:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 20:04:55 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_charcmp(char c1, char c2)
{
	if (c1 == c2)
		return (0);
	return (1);
}

int	ft_go_next_quote(char *input, int i, char quote)
{
	while (input[i++])
	{
		if (ft_charcmp(input[i], quote) == 0)
			return (i);
	}
	return (-1);
}

int	check_quotes(char *input)
{
	int	i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == 92 && input[i + 1])
			i++;
		else if (input[i] == 92 && !input[i + 1])
			return (error_msg("error near \\"));
		else if (input[i] == 34 || input[i] == 39) // " o '
		{
			quote = input[i];
			i = ft_go_next_quote(input, i, quote);
			if (i == -1)
				return (error_msg("error: missing quote\n"));
		}
		i++;
	}
	return (0);	
}

void	which_quote2(t_qte *q, char *arg, int *i, t_data *d)
{
	if (arg[*i] == 92 && arg[*i + 1])
	{
		*i += 2;
		q->startwq = *i - 1;
	}
	else if (arg[*i] == 39 || arg[*i] == 34)
	{
		q->new = replace_quote(q, i, d);
		q->startwq = *i;
	}
}
