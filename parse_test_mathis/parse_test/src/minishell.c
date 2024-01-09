/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:46:33 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/09 13:19:12 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(void)
{
	t_data	d;

//	d = (t_data *)malloc(sizeof(t_data));
	while (1)
	{
		d.input = readline("$>");	// llama la palabras
		if (d.input == NULL)
			return (1);
		d.t = max_split(&d);		// hace un split del input
		if (d.t == NULL)
		{
			free(d.input);
			return (1);
		}
		ft_exec(&d, 0);			// exec la primera funcion (0) por el momiento
		freeall(d.t, ((d.nb_f * 2) - 1));
		d.nb_f = 0;
		free(d.input);
	}
	return (0);
}
