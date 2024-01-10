/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:46 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 18:13:37 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// te dice si el char es '|'

int	is_redirection(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

// te dice si las palabras despues son solo blanco o hay cossas

int	no_blanc_space(char *input, int i)
{
	while (input[i])
	{
		if (ft_isprint(input[i]) && input[i] != '|'
			&& input[i] != 32 && input[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

int	get_nb_funcion(char *input)
{
	int	i;
	int	nb_f;

	i = 0;
	nb_f = 0;
	while (input[i])
	{
		while (input[i] && input[i] != '|')
			i++;
		if (input[i] && input[i] == '|')
		{
			if (!no_blanc_space(input, i))
			{
				printf("parsing error near '|'");
				return (0);
			}
			while (input[i] == '|')
				i++;
		}
		nb_f++;
	}
	return (nb_f);
}

char	**free_splited_input(char **splited_input, int i)
{
	while (i >= 0)
		free(splited_input[i--]);
	free(splited_input);
	return (NULL);
}

char	**split_input(t_data *d, int start, int len, int i)
{
	char	**splited_input;

	splited_input = (char **)malloc(sizeof(char *) * (d->nb_f + 1));
	if (!splited_input)
		return (NULL);
	while (d->input[len])
	{
		while (d->input[len] && !is_redirection(d->input[len]))
			len++;
		splited_input[i++] = ft_substr(d->input, start, len);
		if (!splited_input[i - 1])
			return (free_splited_input(splited_input, i - 1));
		if (is_redirection(d->input[len]))
			splited_input[i++] = ft_substr(d->input, len, 1);
		if (!splited_input[i - 1])
			return (free_splited_input(splited_input, i - 1));
		while (d->input[len] == '|')
			len++;
		start = len;
	}
	splited_input[i] = NULL;
	return (splited_input);
}
