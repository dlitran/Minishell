/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:40:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/09 13:11:58 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// hace un split de las funcionas como eso:
// input = ls | cat -e
// split = "ls", "|", "cat -e"

char	***max_split(t_data *d)
{
	char	***t;
	int	i;
	int	j;
	size_t	len;

	d->nb_f = get_nb_function(d->input);
	t = (char ***)malloc(sizeof(char **) * ((d->nb_f * 2)));
	if (!t)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ((d->nb_f * 2) - 1))
	{
		len = find_redirection(d->input, j);
		t[i] = ft_split(ft_substr(d->input, j, len - j), ' ');
		if (!t[i])
			return (freeall(t, i));
		j = len;
		i++;
	}
	t[i] = NULL;
	return (t);
}
