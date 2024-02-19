/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:22:18 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/19 12:52:41 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_arg(char *input, int *i, t_data *d)
{
	char	**ret;
	int		k;
	int		start;

	k = 0;
	ret = ft_calloc(sizeof(char *), d->cmd->nb_arg + 2);
	if (!ret)
		return (1);
	while (k < d->cmd->nb_arg)
	{
		*i = ft_skip_space(input, *i);
		start = *i;
		*i = ft_go_next_space(input, *i);
		ret[k] = ft_substr_mnsh(input, start, *i - start, d);
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
	d->nb_f += 1;
	get_nb_arg(input, *i, d);
	get_arg(input, i, d);
	if (d->cmd->arg == NULL)
		return (error_msg("error allocating memory for args\n"));
	d->cmd->exe = d->cmd->arg[0];
	//parse_quotes(d, 0);
	return (0);
}

int	parse(char *input, t_data *d)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (get_cmd(input, d, &i) == 1)
			return (free_cmd_parsing(d, d->first));
		i = ft_skip_space(input, i);
		if (!input[i])
		{
			d->cmd = d->first;
			return (0);
		}
		get_redirection(input, &i, d);
		d->cmd->next = ft_new_cmd();
		if (d->cmd->next == NULL)
			return (free_newcmd_parsing(d, d->first));
		d->cmd = d->cmd->next;
	}
	d->cmd = d->first;
	return (0);
}

int	ft_parse_input(char *input, t_data *d)
{
	if (check_quotes(input) == 1)
		return (1);
	if (check_pipe(input) == 1)
		return (1);
	if (check_redir(input) == 1)
		return (1);
	d->cmd = ft_new_cmd();
	if (d->cmd == NULL)
		return (error_msg("error allocating memory for cmd list\n"));
	d->first = d->cmd;
	if (parse(input, d) == 1)
		return (1);
	return (0);
}