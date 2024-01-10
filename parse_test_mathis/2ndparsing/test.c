/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:25:14 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 21:42:54 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	pid_t	child_pid;
	int	i;
	char const **arg;

	i = 0;
	child_pid = fork();
	arg[0] = "/bin/ls";
	arg[1] = "-la";
	if (child_pid < 0)
	{
		printf("error fork\n");
		return (0);
	}
	else if (child_pid == 0)
	{
		int	i;

		i = 0;
		(void)i;
		execve(arg[0], (char * const *)arg, NULL);
	}
	else
		wait(0);
	return (0);
}
