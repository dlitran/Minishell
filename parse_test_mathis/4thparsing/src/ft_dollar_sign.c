/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:42 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/07 23:44:05 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_dollar_sign(t_data *d)
{
	int	i;
	int	j;

	i = 1;
	while (d->cmd->exe[i])
		i++;
	j = 0;
	while (d->env[j])
	{
		if (strncmp(d->env[j], &d->cmd->exe[1], i - 1) == 0)
		{
			printf("%s\n", &d->env[j][i]);
			return ;
		}
		j++;
	}	
}
