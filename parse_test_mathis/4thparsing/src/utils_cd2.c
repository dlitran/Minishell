/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:01:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/18 18:49:36 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

char	*cd_before(char *path)
{
	char	*tmp;

	if (ft_strrchr(path, '/') - path == 0)
		tmp = ft_strdup("/");
	else
		tmp = ft_substr(path, 0, (ft_strrchr(path, '/') - path));
	free(path);
	return (tmp);
}
