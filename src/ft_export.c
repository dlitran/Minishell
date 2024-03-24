/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:08:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/18 18:55:28 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ex_replace(t_data *d, int i, int j)
{
	char	*new;

	new = ft_strdup(d->cmd->arg[i]);
	if (!new)
		return (error_msg("error allocating memory for ft_export\n", 57));
	free(d->env[j]);
	d->env[j] = new;
	if (!ft_strncmp(new, "PATH=", 5))
	{
		free(d->path);
		d->path = new;
	}
	return (0);
}

int	ex_insert(t_data *d, int i)
{
	int		len;
	char	**new;

	len = 0;
	while (d->env[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (error_msg("error allocating memory for ft_export\n", 54));
	len = 0;
	while (d->env[len])
	{
		new[len] = ft_strdup(d->env[len]);
		if (!new[len])
			return (free_env2(new, len, 55, 1));
		len++;
	}
	new[len] = ft_strdup(d->cmd->arg[i]);
	if (!new[len])
		return (free_env2(new, len, 56, 1));
	new[len + 1] = NULL;
	free_env2(d->env, len, -1, 0);
	d->env = new;
	return (0);
}

int	ft_valid_identifier(char **name, int i, int err)
{
	int	c;
	int	j;

	c = 1;
	while (name[i])
	{
		j = 0;
		if (!ft_isalpha(name[i][0]) && name[i][0] != '_')
			return (prt_err(name[i], err));
		while (name[i][j] && name[i][j] != '=')
		{
			if (!ft_isalnum(name[i][j]) && name[i][j] != '_')
				return (prt_err(name[i], err));
			if (!(name[i][j] > 47 && name[i][j] < 58))
				c = 0;
			j++;
		}
		if (c == 1)
			return (prt_err(name[i], err));
		i++;
	}
	return (0);
}

void	ft_export(t_data *d, int i, int j)
{
	if (ut_export(d, i))
		return ;
	while (d->cmd->arg[i])
	{
		if (find_equal(d->cmd->arg[i]) > 0)
		{
			j = 0;
			while (d->env[j] && ft_strncmp(d->cmd->arg[i], d->env[j],
					find_equal(d->cmd->arg[i])) != 0)
				j++;
			if (!d->env[j])
			{
				if (ex_insert(d, i) == 1)
					return ;
			}
			else
			{
				if (ex_replace(d, i, j) == 1)
					return ;
			}
		}
		i++;
	}
	g_error = 0;
}
