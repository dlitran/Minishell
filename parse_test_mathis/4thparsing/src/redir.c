/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:29:45 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 01:05:15 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_redir(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		i = ft_skip_space(input, i);
		if (input[i] == '|')
			c = 1;
		else if (input[i] == '<' || input[i] == '>')
		{
			if (c == 1)
				return (error_msg("error near redirection\n"));
			c = 1;
			if (input[i + 1] && input[i + 1] == input[i])
				i++;		
		}
		else
			c = 0;
		i++;
	}
	return (0);
}
