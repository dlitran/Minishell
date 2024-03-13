/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:51:06 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 00:58:08 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	prt_err(char *str)
{
	char	*complex_err;
	char	*tmp;

	tmp = ft_strjoin(str, "': not a valid identifier\n");
	if (!tmp)
		return (v_err_msg("error strjoin\n", 95));
	complex_err = ft_strjoin("export: '", tmp);
	free(tmp);
	if (!complex_err)
		return (v_err_msg("error strjoin\n", 96));
	perror(complex_err);
	free(complex_err);
	g_error = 1;
}
