/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:02:50 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/16 20:16:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (d->env[i])
		i++;
	while (i >= 0)
	{
		free(d->env[i]);
		i--;
	}
	free(d->env);
	free(d->path);
	free(d);
}
