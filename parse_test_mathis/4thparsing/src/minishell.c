/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/19 18:04:11 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	show_values(t_data *d)
{
	printf("All went well, the input is good\n");
	int	i;
	int	nb = 1;
	while (d->cmd)
	{
		i = 0;
		printf("\n\nfuncion number: %d\n", nb);
		printf("funcion: %s\n", d->cmd->exe);
		while (d->cmd->arg[i])
		{
			printf("arg %d: %s\n", i + 1, d->cmd->arg[i]);
			i++;
		}
		printf("| : %d, < : %d, << : %d, > : %d, >> : %d\n", d->cmd->pipe, d->cmd->inferior, d->cmd->inferior_two, d->cmd->superior, d->cmd->superior_two);
		d->cmd = d->cmd->next;
		nb++;
	}
	printf("\n");
}

void	exec_funcion(t_data *d)
{
	//show_values(d);
	int	i;

	i = 0;
	//d->tmp_stdin = dup(0);
	//d->tmp_stdout = dup(1);
	d->nb_pipes = ft_nb_pipes(d);
	d->infile = ft_infile(d); //Comprueba si hay infile (< o <<)
	d->outfile = ft_outfile(d); //Comprueba si hay outfile (> o >>)
	if (d->nb_pipes > 0)
	{
		d->pipe = malloc(sizeof(int *) * d->nb_pipes);
		while (i < d->nb_pipes)
		{
			d->pipe[i] = malloc(sizeof(int) * 2); //cada pipe tiene 2 extremos.
			i++;
		}
		i = 1;
		d->pid = malloc(sizeof(pid_t) * (d->nb_pipes + 1));
		d->pid[0] = fork();
		if (d->pid[0] == 0)
		{
			while (i < d->nb_pipes + 1 && d->pid[i - 1] == 0)
			{
				pipe(d->pipe[i -1]);
				d->pid[i] = fork ();
				i++;
			}
			i--;
			if (d->pid[i] != 0)
				waitpid(d->pid[i], NULL, 0);
			if (i == d->nb_pipes && d->pid[i] == 0)
				ft_first_process(d); // ejecuta pipe + 1
			else if (i == 1)
				ft_last_process(d); // ejecuta pipe 0
			else
				ft_child(d, i); // ejecuta pipes + 1 - i
			exit (0);
		}
		waitpid(d->pid[0], NULL, 0);
		return ;
	}
	else
	{
		ft_no_pipe(d);
	}
}

void	start_shell(t_data *d)
{
	char	*input;

	while (1)
	{
		input = readline("$>");
		if (!input)
		{
			error_msg("error reading input from readline\n");
			return ;
		}
		if (ft_is_blank(input) == 1 || input[0] == '\0')
			free(input);	// si hay nada en el input o solo espacios
		else
		{
			add_history(input);
			if (ft_parse_input(input, d) == 0) // todo el parsing aqui (ft_parse_input.c))
				exec_funcion(d);	//	arriba
			free_commands(d, input);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	if (argc != 1)
		return (error_msg("minishell.c does not need any arguments\n"));
	(void)argv;
	d = ft_calloc(sizeof(t_data), 1);
	if (!d)
		return (error_msg("error while allocating memory for data\n"));
	if (ft_getenv(d, envp) == 1)	//	Cogemos el environemiento dentro un char** en la data
		return (error_msg("error while getting environment\n"));
	start_shell(d);	//	arriba
	free_data(d);
	return (0);
}
