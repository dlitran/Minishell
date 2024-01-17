/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:38:09 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 01:23:30 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_arg(char **arg, int k)
{
	k--;
	while (k >= 0)
	{
		free(arg[k]);
		k--;
	}
	free(arg);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}


void	get_redirection(char *input, int *i, t_data *d)
{
	if (input[*i] == '|')
	{
		while (input[*i] == '|')
			*i += 1;
		d->cmd->pipe = 1;
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		if (input[*i] && input[*i] == '<')
			d->cmd->inferior_two = 1;
		else
			d->cmd->inferior = 1;
	}
	else if (input[*i] == '>')
	{
		*i += 1;
		if (input[*i] && input[*i] == '>')
			d->cmd->superior_two = 1;
		else
			d->cmd->superior = 1;
	}
}

void	get_nb_arg(char *input, int i, t_data *d)
{
	int	nb_arg;

	nb_arg = 0;
	while (input[i])
	{
		i = ft_skip_space(input, i);
		if (!input[i] || input[i] == '|' || input[i] == '<'
			|| input[i] == '>')
		{
			d->cmd->nb_arg = nb_arg;
			return ;
		}
		nb_arg++;
		i = ft_go_next_space(input, i);
	}
	d->cmd->nb_arg = nb_arg;
	return ;
}