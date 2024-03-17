/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:23:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 11:06:46 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_charcmp(char c1, char c2)
{
	if (c1 == c2)
		return (0);
	return (1);
}

int	ft_go_next_quote(char *input, int i, char quote)
{
	while (input[i])
	{
		if (ft_charcmp(input[i], quote) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

static int	cq_end(char c)
{

	ft_putstr_fd("error: unexpected EOF while looking for matching `", 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\"\n", 2);
	g_error = 2;
	return (1);
}

int	check_quotes(char *input)
{
	int		i;
	char		c;

	i = 0;
	while (input[i])
	{
		if (input[i] == 92 && !input[i + 1])
			return (error_msg("error near \\", 0));
		else if (input[i] == 34 || input[i] == 39)
		{
			c = input[i];
			i = ft_go_next_quote(input, i + 1, input[i]);
			if (i == -1)
				return (cq_end(c));
		}
		i++;
	}
	return (0);
}
