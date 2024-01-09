/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:59:49 by mafranco          #+#    #+#             */
/*   Updated: 2023/11/28 19:09:12 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_special(char	*str)
{
	if (!str)
		return (-1);
	if (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		return (2);
	if (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		return (3);
	if (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2)
		return (4);
	if (ft_strncmp(str, "|", 1) == 0 && ft_strlen(str) == 1)
		return (5);
	return (0);
}

int	get_nb_function(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (str[i])
	{
		/*if (is_special(str[i]) > 0)
			nb++;*/
		if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|'))
		{
			nb++;
			if ((str[i] == '<') || (str[i] == '>') || (str[i] == '|'))
				i++;
		}
		i++;
	}
	return (nb);
}

size_t	find_redirection(char *str, size_t len)
{
	while (str[len] == ' ')
		len++;
	if (str[len] == '<' || str[len] == '>' || str[len] == '|')
	{
		len++;
		if (str[len] == '<' || str[len] == '>')
		{
			len++;
		}
		return (len);
	}
	while (str[len])
	{
		while (str[len] == ' ')
			len++;
		if (str[len] == '<' || str[len] == '>' || str[len] == '|')
			return (len);
		len++;
	}
	return (len);
}
