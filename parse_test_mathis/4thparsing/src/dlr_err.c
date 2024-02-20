/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlr_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:26:53 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/20 17:42:04 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	dlr_interrogation(t_data *d, t_qte *qte, int *i)
{
	char	*err;

	(void)d;
	err = ft_itoa(nb_error);
	qte->new = add_in_front2(err, qte, 0, ft_strlen(err));
	if (err)
		free(err);
	*i += 2;
}
