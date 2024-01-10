/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:47:40 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 22:46:10 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**init_arg(const char *funcion)
{
	char	**arg;
	char	*f;
	char	*t;
	int	i;

	i = 0;
	arg = (char **)malloc(sizeof(char *) * 3);
	if (!arg)
	{
		printf("error malloc\n");
		return (NULL);
	}
	f = ft_strtrim(funcion, " \t\v");
	while (f[i] && f[i] != ' ' && f[i] != '\t' && f[i] != '\v')
		i++;
	arg[0] = ft_substr(f, 0, i);
	t = ft_substr(f, i, ft_strlen(f) - i);
	free(f);
	arg[1] = ft_strtrim(t, " \t\v");
	free(t);
	arg[2] = NULL;
	return (arg);
}

void	do_execve(t_data *d, char **arg)
{
	int	i;
	int	x;
	char	*f;

	i = 0;
	f = ft_strdup(arg[0]);
	while (d->path[i])
	{
		arg[0] = ft_strjoin(d->path[i], f);
		x = execve(arg[0], (char * const *)arg, NULL);
		if (x != -1)
		{
			free(arg[1]);
			free(arg[0]);
			free(arg);
			free(f);
			return;
		}
		i++;
	}
	free(arg[1]);
	free(arg[0]);
	free(arg);
	free(f);
	printf("command not found: %s\n", d->input);
}

void	ft_execve(t_data *d, char *funcion)
{
	pid_t	pid;
	char	**arg;

	arg = NULL;
	pid = fork();
	if (pid < 0)
	{
		printf("error fork\n");
		return;
	}
	else if (pid == 0)
	{
		arg = init_arg(funcion);
		do_execve(d, arg);
	}
	else
	{
		wait(0);
	}
}
