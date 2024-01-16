/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:00:51 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/16 21:17:32 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_pipe(char *input, t_data *d)
{
	int	i;
	int	c;

	(void)d;
	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			while(input[i] == '|')
					i++;
			if (c == 0)
				return (error_msg("error near '|'\n"));
			c = 0;
		}
		else
			c = 1;
		i++;
	}
	if (c == 0)
		return (error_msg("error near '|'\n"));
	return (0);
}
