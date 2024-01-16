/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 00:24:16 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	exec_funcion(t_data *d)
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
			free(input);
		else
		{
			add_history(input);
			if (ft_parse_input(input, d) == 0)
				exec_funcion(d);
			free(input);
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
	if (ft_getenv(d, envp) == 1)
		return (error_msg("error while getting environment\n"));
	start_shell(d);
	free_data(d);
	return (0);
}
