/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:35:00 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/20 20:26:13 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	error_msg(char *str, int nb)
{
	perror(str);
	nb_error = nb;
	return (1);
}

void	v_err_msg(char *str, int nb)
{
	perror(str);
	nb_error = nb;
}

char	*c_err_msg(char *str, int nb)
{
	perror(str);
	nb_error = nb;
	return (NULL);
}
