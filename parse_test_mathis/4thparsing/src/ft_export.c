/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:08:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/21 00:51:02 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	prt_err(char *str, int nb)
{
	printf("export: `%s`: not a valid identifier\n", str);
	g_error = nb;
}

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
		return (error_msg("error allocating memory for ft_export", 57));
	free(d->env[j]);
	d->env[j] = new;
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

void	ft_export(t_data *d, int i, int j)
{
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
		else
			prt_err(d->cmd->arg[i], 58);
		i++;
	}
	g_error = 0;
}
