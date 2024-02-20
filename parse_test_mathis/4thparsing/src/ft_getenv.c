/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:33:28 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/20 19:35:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	free_env(char **env, int i, int nb)
{
	i--;
	while (i >= 0)
	{
		free(env[i]);
		i--;
	}
	free(env);
	return (error_msg("error allocating memory for environment\n", nb));
}

int	ft_getenv(t_data *d, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	d->env = ft_calloc(i, sizeof(char *));
	if (d->env == NULL)
		return (error_msg("error allocating memory for environment\n", 3));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			d->env[i] = ft_strdup("SHLVL=2");
		else
		{
			d->env[i] = ft_strdup(envp[i]);
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				d->path = ft_substr(d->env[i], 5, ft_strlen(d->env[i]));
		}
		if (d->env[i] == NULL)
			return (free_env(d->env, i, 4));
		i++;
	}
	d->env[i] = NULL;
	return (0);
}
