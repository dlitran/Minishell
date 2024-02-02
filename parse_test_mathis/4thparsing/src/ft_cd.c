/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:29 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/02 09:22:49 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_add_oldpwd(t_data *d)
{
	char	**new;
	int		i;

	i = 0;
	while (d->env[i])
		i++;
	new = ft_calloc((i + 2), sizeof(char *));
	if (!new)
		return (NULL);
		//Error management
	i = 0;
	while (d->env[i])
	{
		new[i] = ft_strdup(d->env[i]);
		free(d->env[i]);
		i++;
	}
	new[i] = ft_strdup("OLDPWD="); //This will be substituted later by the actual OLDPWD
	free(d->env);
	return (new);
}

void	ft_set_env(t_data *d, char *path)
{
	int	i;
	int	j;

	i = 0; //PWD position
	j = 0; //OLDPWD position
	while (d->env[j] && ft_strncmp(d->env[j], "OLDPWD=", 7) != 0)
		j++;
	if (!d->env[j])
		d->env = ft_add_oldpwd(d);
	while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
		i++;
	free(d->env[j]);
	d->env[j] = ft_strdup(ft_strjoin("OLDPWD=", (d->env[i] + 4)));
	free(d->env[i]);
		d->env[i] = ft_strdup(ft_strjoin("PWD=", path));
	return ;
}

char	*ft_path(t_data *d)
{
	char	*path;
	char	**arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arg = ft_split(d->cmd->arg[1], '/');
	while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
		i++;
	path = ft_strdup(d->env[i] + 4);
	while (arg[j])
	{
		if (!strncmp(arg[j], "..", 3)) // if arg[j] i ".."
			path = ft_substr(path, 0, (ft_strrchr(path, '/') - path));
		else if (strncmp(arg[j], ".", 2)) //if arg[j] i not "."
			path = ft_strjoin(path, ft_strjoin("/", arg[j]));
		free(arg[j]);
		j++;
	}
	free(arg);
	return (path);
}

char	*ft_home(t_data *d)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp(d->env[i], "HOME=", 5))
		i++;
	path = ft_strdup(d->env[i] + 5);
	return (path);
}

void	ft_cd(t_data *d)
{
	int		i;
	char	*path;

	i = 0;
	while (d->cmd->arg[i])
		i++;
	if (i > 2)
	{
		printf("-bash: cd too many arguments\n");
		return ;
	}
	if ((i == 1 && !d->cmd->arg[1]) || !ft_strncmp(d->cmd->arg[1], "~", 1))
		path = ft_home(d);
	else if (d->cmd->arg[1][0] == '/')
		path = ft_strdup(d->cmd->arg[1]);
	else
		path = ft_path(d);
	if (chdir(path) == -1)
	{
		printf("-bash: cd: %s: No such file or directory\n", d->cmd->arg[1]);
		return ;
	}
	ft_set_env(d, path);
	free(path);
}
