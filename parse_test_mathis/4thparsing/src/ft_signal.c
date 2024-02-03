/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:58:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/03 17:23:11 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_sigint()
{
	if (isatty(STDIN_FILENO))
	{
		//printf("SIGINT CAPTURED INTERACTIVE MODE\n");
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
	//	printf("SIGINT CAPTURED NOT INTERACTIVE\n");
	}
}

void	handle_sigquit()
{
	if (isatty(STDIN_FILENO))
	{
		//printf("SIGQUIT CAPTURED IN INTERACTIVE MODE\n");
		rl_redisplay();
	}
	else
	{
	//	printf("SIGQUIT CAPTURED NOT IN INTERACTIVE MODE");
		exit(0);
	}
}

void	wait_signal()
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("Error configurating sigint");
		return ;
	}
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
	{
		perror("Error configurating sigquit");
		return ;
	}
}

