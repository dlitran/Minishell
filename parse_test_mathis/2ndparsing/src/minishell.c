/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:21:55 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 22:44:54 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	while (i >= 0)
	{
		free(path[i]);
		i--;
	}
	free(path);
}

void	free_all(t_data *d)
{
	int	i;

	i = 0;
	while (d->f[i])
		i++;
	while (i >= 0)
	{
		free(d->f[i]);
		i--;
	}
	free(d->f);
	free(d->input);
}

int	main(void)
{
	t_data	d;

	d.path = get_path();

	//while (1)
	//{
		d.input = readline("$>");
		if (d.input == NULL)
			return (0);
		//	break;
		d.nb_f = get_nb_funcion(d.input);
		if (d.nb_f == 0)
			return (0);
		d.f = split_input(&d, 0, 0, 0);
		if (!d.f)
		{
			free(d.input);
			return (0);
		}
		ft_exec_funcion(&d);
		/*int	i = 0; //	SHOW THE SPLIT OF THE INPUT
		while (d.split_input[i])
		{
			printf("%s\n", d.split_input[i]);
			i++;
		}*/
		free_all(&d);
	//}
	/*int	i = 0;
	while (d.path[i])	//	SHOW THE SPLIT OF THE PATH
	{
		printf("%s\n", d.path[i]);
		i++;
	}*/
	free_path(d.path);
	return (0);
}
