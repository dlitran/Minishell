/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_in_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:25:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 03:04:14 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*return_error_quotes(char *new)
{
	if (new)
		free(new);
	perror("error allocating memory for quote parsing");
	return (NULL);
}

int	find_next_space(char *input, int i)
{
	while (input[i] && (input[i] != ' ' && input[i] != '\t'
		&& input[i] != '\n' && input[i] != '\f' && input[i] != '\r'
		&& input[i] != '\v'))
		i++;
	return (i);
}

char	*insert_dlr(char *new, char *dlr, t_data *d)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(dlr);
	while (d->env[j])
	{
		if (strncmp(d->env[j], dlr, len) == 0)
		{
			new = add_in_front(d->env[j], new, len, ft_strlen(d->env[j] - len));
			return new;
		}
		j++;
	}
	return (new);
}

char	*isrt_dlr_in_arg(const char *arg, char *new, int i, int nba, t_data *d)
{
	char	*dlr;
	int	start;

	write(1, "gogogo", 6);
	start = i;
	dlr = NULL;
	while (arg[i] && arg[i] != 34)
	{
		if (arg[i] == '$' && !(i == start && nba == 0))
		{
			new = add_in_front(arg, new, start, start - i);
			dlr = ft_substr((char *)arg, i + 1, find_next_space((char *)arg, i) - i + 1);
			if (!new)
				return (return_error_quotes(NULL));
			if (!dlr)
				return (return_error_quotes(new));
			new = insert_dlr(new, dlr, d);
			if (!new)
				return (return_error_quotes(NULL));
			i = find_next_space((char *)arg, i);
			start = i;
		}
		else
			i++;
	}
	new = add_in_front(arg, new, start, start - i);
	return new;
}
