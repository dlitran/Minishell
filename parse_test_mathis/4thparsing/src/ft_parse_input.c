/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:22:18 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/12 13:17:10 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_arg(char *input, int *i, t_data *d)
{
	char	**ret;	//	es para hacer un char ** (ret aqui) con todos los argumentos
	int	k;
	int	start;

	k = 1;
	ret = ft_calloc(sizeof(char *), d->cmd->nb_arg + 2);
	if (!ret)
		return (1);
	ret[0] = ft_substr(d->cmd->exe, 0, ft_strlen(d->cmd->exe));
	while (k < d->cmd->nb_arg + 1)
	{
		*i = ft_skip_space(input, *i);
		start = *i;
		*i = ft_go_next_space(input, *i);
		ret[k] = ft_substr(input, start, *i - start);
		if (!ret[k])
		{
			free_arg(ret, k);
			return (1);
		}
		k++;
	}
	ret[k] = NULL;
	d->cmd->arg = ret;
	return (0);
}

int	get_cmd(char *input, t_data *d, int *i)
{
	int	start;	// aqui es para tener la primera palabra del input (la command)

	d->nb_f += 1;
	printf("char de depart de la funcion get_cmd : $%s$i = %d\n", *i + input, *i);
	*i = ft_skip_space(input, *i); // utils.c
	start = *i;
	*i = ft_go_next_space(input, *i); // utils.c
	d->cmd->exe = ft_substr(input, start, *i - start);
	printf("d-/cmd-/exe = $>%s$, start = %d, i - start = %d\n", d->cmd->exe, start, *i - start);
	if (!d->cmd->exe)
		return (error_msg("error allocating memory for cmd\n"));
	get_nb_arg(input, *i, d); // utils_parse.c
	get_arg(input, i, d); // arriba
	if (d->cmd->arg == NULL)
	{
		free(d->cmd->exe);
		return (error_msg("error allocating memory for args\n"));
	}
	return (0);
}

int	parse(char *input, t_data *d)
{
	int	i;
	t_cmd	*first;

	i = 0;
	first = d->cmd; // para tener la primera
	while (input[i])
	{
		if (get_cmd(input, d, &i) == 1) // arriba
			return (free_cmd_parsing(d, first));
		i = ft_skip_space(input, i);
		if (!input[i])
		{
			d->cmd = first;
			return (0);
		}
		get_redirection(input, &i, d); // utils_parse.c
		d->cmd->next = ft_new_cmd(); // utils_parse.c
		if (d->cmd->next == NULL)
			return (free_newcmd_parsing(d, first));
		d->cmd = d->cmd->next;
		//i++;
	}
	d->cmd = first;
	return (0);
}

int	ft_parse_input(char *input, t_data *d)
{
	if (check_quotes(input) == 1)	// para saber si no se falta quote " '
		return (1);
	if (check_pipe(input) == 1)	// para saber si no hay problema con los | (no hay 2 |, o <| o | |...)
		return (1);
	if (check_redir(input) == 1)	// mismo pero por las redireciones
		return (1);
	d->cmd = ft_new_cmd();	//	hace una nueva lista cmd (puedes ver el archivo header.h)
	d->first = d->cmd;
	if (d->cmd == NULL)
		return (error_msg("error allocating memory for cmd list\n"));
	if (parse(input, d) == 1)	//	arriba
		return (1);
	return (0);
}
