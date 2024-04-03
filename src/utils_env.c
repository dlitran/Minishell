/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:52:46 by mafranco          #+#    #+#             */
/*   Updated: 2024/04/03 15:55:32 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_env_export2(char *env, int j)
{
	printf("=");
	j += 1;
	printf("\"");
	while (env[j])
	{
		printf("%c", env[j]);
		j++;
	}
	printf("\"\n");
}
