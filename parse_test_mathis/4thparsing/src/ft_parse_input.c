/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:22:18 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 00:20:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_arg(char *input, int *i, t_data *d, int nb_arg)
{
	char	**ret;
	int	k;
	int	start;

	k = 0;
	ret = ft_calloc(sizeof(char *), nb_arg + 1);
	if (!ret)
		return (1);
	while (k < nb_arg)
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
//	int	i;
	int	start;
	int	nb_arg;

//	i = 0;
	*i = ft_skip_space(input, *i);
	start = *i;
	*i = ft_go_next_space(input, *i);
	d->cmd->exe = ft_substr(input, start, *i - start);
	if (!d->cmd->exe)
		return (error_msg("error allocating memory for cmd\n"));
	nb_arg = get_nb_arg(input, *i);
	get_arg(input, i, d, nb_arg);
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
	first = d->cmd;
	while (input[i])
	{
		if (get_cmd(input, d, &i) == 1)
			return (1);	//	free las cmd antes
		i = ft_skip_space(input, i);
		if (!input[i])
		{
			d->cmd = first;
			return (0);
		}
		get_redirection(input, &i, d);
		d->cmd->next = ft_new_cmd();
		if (d->cmd->next == NULL)
			return (1);	//	free las cmd antes
		d->cmd = d->cmd->next;
		i++;
	}
	d->cmd = first;
	return (0);
}

int	ft_parse_input(char *input, t_data *d)
{
	if (check_quotes(input) == 1)
		return (1);
	if (check_pipe(input, d) == 1)
		return (1);
	d->cmd = ft_new_cmd();
	if (d->cmd == NULL)
		return (error_msg("error allocating memory for cmd list\n"));
	if (parse(input, d) == 1)
		return (1);
	return (0);
}
