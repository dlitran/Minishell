/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:29:45 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/19 21:32:14 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	dbl_inf(int c, char *input, int *i, t_data *d)
{
	(void)d;
	if (c == 1)
		return (error_msg("error near redirection\n", 12));
	if (input[*i + 1] && input[*i + 1] == input[*i])
	{
		*i += 1;
		if (input[*i] == '<')
		{
			*i = ft_skip_space(input, *i);
			if (input[*i] == '!' && input[*i])
				return (error_msg("error : event not found\n", 0));
			else if (!ft_isprint(input[*i]))
				return (error_msg(
						"syntax error near \
						unexpected token `newline'\n", 258));
			while (ft_isprint(input[*i]) && input[*i] != ' ')
				*i += 1;
		}	
	}
	return (0);
}

int	check_redir(char *input, t_data *d)
{
	int	i;
	int	c;

	(void)d;
	i = 0;
	c = 0;
	while (input[i])
	{
		if ((input[i] == 39 || input[i] == 34) && input[i + 1])
			i = ft_go_next_quote(input, i + 1, input[i]);
		else if (input[i] == '|')
			c = 1;
		else if (input[i] == '<' || input[i] == '>')
		{
			//if (c == 1)
			//	return (error_msg("error near redirection\n", 12));
			if (dbl_inf(c, input, &i, d) == 1)
				return (1);
			c = 1;
			//if (input[i + 1] && input[i + 1] == input[i])
			//	i++;
		}
		else
			c = 0;
		i++;
	}
	return (0);
}
