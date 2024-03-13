/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 01:25:04 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	exec_funcion(t_data *d)
{
	d->tmp_stdin = dup(0);
	if (d->tmp_stdin == -1)
		v_err_msg("error duplicating file descriptor\n", 101);
	d->tmp_stdout = dup(1);
	if (d->tmp_stdout == -1)
		v_err_msg("error duplicating file descriptor\n", 102);
	d->nb_pipes = ft_nb_pipes(d);
	d->infile = ft_infile(d);
	d->outfile = ft_outfile(d);
	if (d->nb_pipes > 0)
		ft_exec_pipe(d, 0);
	else
		ft_no_pipe(d);
	if (dup2(d->tmp_stdin, 0) == -1)
		v_err_msg("error duplicating file descriptor\n", 103);
	if (dup2(d->tmp_stdout, 1) == -1)
		v_err_msg("error duplicating file descriptor\n", 104);
}

void	start_shell(t_data *d)
{
	while (1)
	{
		d->input = readline("$>");
		if (!d->input)
			return ;
		if (ft_is_blank(d->input) == 1 || d->input[0] == '\0')
			free(d->input);
		else
		{
			if (ft_parse_input(d->input, d) == 0)
			{
				exec_funcion(d);
				add_history(d->input);
				free_commands(d, d->input);
			}
			else
			{
				add_history(d->input);
				free(d->input);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	g_error = 0;
	if (argc != 1)
		return (error_msg("minishell.c does not need any arguments\n", 1));
	(void)argv;
	d = ft_calloc(sizeof(t_data), 1);
	if (!d)
		return (error_msg("error while allocating memory for data\n", 2));
	if (ft_getenv(d, envp) == 1)
		return (1);
	wait_signal();
	start_shell(d);
	free_data(d);
	return (0);
}
