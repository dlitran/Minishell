/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:00:51 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 21:39:45 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_pipe(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		i = ft_skip_space(input, i);
		if (input[i] == '<' || input[i] == '>')
			c = 0;
		else if (input[i] == '|')
		{
			if (c == 0)	//	si hay un < o > antes del '|' o si el '|' es el primer char
				return (error_msg("error near '|'\n"));
			c = 0;
		}
		else
			c = 1;	//	si hay char, hace un reset de c
		i++;
	}
	if (c == 0)
		return (error_msg("error near '|'\n"));
	return (0);
}
