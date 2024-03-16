/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:58:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 21:38:23 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	handle_sigint(int i)
{
	(void)i;
	if (isatty(1))
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_error = 130;
	}
	else
	{
		g_error = 130;
	}
}

void	handle_sigquit(int i)
{
	(void)i;
	if (!(isatty(1)))
	{
		g_error = 131;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	wait_signal(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("Error configurating sigint\n");
		g_error = 5;
		return ;
	}
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
	{
		perror("Error configurating sigquit\n");
		g_error = 6;
		return ;
	}
}
