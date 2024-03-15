/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:31:15 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/13 01:25:29 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

char	*err_cd_dbl_pt(int nb, char *path)
{
	g_error = nb;
	free(path);
	printf("error allocating memory with ft_strjoin\n");
	return (NULL);
}

char	*free_all_cd_arg(char **arg, int j)
{
	while (arg[j])
	{
		free(arg[j]);
		j++;
	}
	free(arg);
	return (NULL);
}

char	*cd_double_point(char *path, char **arg, int mode, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (mode == 1)
		tmp = ft_substr(path, 0, (ft_strrchr(path, '/') - path));
	else if (mode == 2)
	{
		tmp2 = ft_strjoin("/", arg[j]);
		if (!tmp2)
			return (err_cd_dbl_pt(47, path));
		tmp = ft_strjoin(path, tmp2);
		if (!tmp)
		{
			free(tmp2);
			return (err_cd_dbl_pt(48, path));
		}
	}
	free(tmp2);
	free(path);
	return (tmp);
}

int	cd_set_pwd(t_data *d, char *path, int i)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", path);
	if (!tmp)
		return (error_msg("error allocating memory with ft_strjoin\n", 51));
	free(d->env[i]);
	d->env[i] = tmp;
	return (0);
}

int	cd_set_oldpwd(t_data *d, int pwd, int i)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", (d->env[pwd] + 4));
	if (!tmp)
		return (error_msg("error allocating memory with ft_strjoin\n", 50));
	free(d->env[i]);
	d->env[i] = tmp;
	return (0);
}
