/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:31:15 by mafranco          #+#    #+#             */
/*   Updated: 2023/11/27 17:12:08 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*freeall(char ***table, int i)
{
	int	j;

	while (i > 0)
	{
		i--;
		j = 0;
		while (table[i][j])
			j++;
		while (j >= 0)
		{
			free(table[i][j]);
			j--;
		}
		free(table[i]);		
	}
	free(table);
	return (NULL);
}
