/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:00:51 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 21:09:54 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	check_pipe(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 1;
	while (input[i])
	{
		//i = ft_skip_space(input, i);
		if ((input[i] == 39 || input[i] == 34) && input[i + 1])
		{
			i = ft_go_next_quote(input, i + 1, input[i]);
			c = 1;
		}
		else if (input[i] == '<' || input[i] == '>')
			c = 0;
		else if (input[i] == '|')
		{
			if (c == 0)
				return (error_msg("error near '|'\n", 10));
			c = 0;
		}
		else
			c = 1;
		i++;
	}
	if (c == 0)
		return (error_msg("error near '|'\n", 11));
	return (0);
}
