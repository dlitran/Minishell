/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:45:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 01:08:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


/*si no es espacio, si es un " o ' se vas al " o ' despues. si se encuentra
  una redirection, se sale*/
int	ft_go_next_space(char *input, int i)
{
	while (input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
		&& input[i] != '\v' && input[i] != '\f' && input[i] != '\r'
		&& input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_go_next_quote(input, i, input[i]);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int	ft_skip_space(char *input, int i)
{
	while ((input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r')
		&& input[i])
		i++;
	return (i);
}

int	ft_is_blank(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '\t' && input[i] != '\n' && input[i] != '\v'
			&& input[i] != '\f' && input[i] != '\r'
			&& input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
