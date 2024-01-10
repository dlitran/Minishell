/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:23:59 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 16:27:46 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**get_path(void)
{
	char	*path;
	char	**path_table;

	path = getenv("PATH");
	path_table = ft_split(path, ':');
	return (path_table);
}
