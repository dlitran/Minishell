/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:59:49 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/09 13:31:59 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


//	para cojer la cmd, no utiliso por el momiento
int	get_command(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 && ft_strlen(str) == 4)
		return (1);
	if (ft_strncmp(str, "cd", 2) == 0 && ft_strlen(str) == 2)
		return (2);
	if (ft_strncmp(str, "pwd", 3) == 0 && ft_strlen(str) == 3)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0 && ft_strlen(str) == 6)
		return (4);
	if (ft_strncmp(str, "unset", 5) == 0 && ft_strlen(str) == 5)
		return (5);
	if (ft_strncmp(str, "env", 3) == 0 && ft_strlen(str) == 3)
		return (6);
	if (ft_strncmp(str, "exit", 4) == 0 && ft_strlen(str) == 4)
		return (7);
	if (ft_strncmp(str, "$", 1) == 0)
		return (8);
	return (9);
}

int	cmd_execve(t_data *d, char *pathenv, int num)
{
	int	i;
	int	j;
	char	*f;
	char	*temp;

	j = -1;
	f = ft_strdup(d->t[num][0]);
	//	hace un execve (ver man execve) del join del path y de la funciona.
	//	Si es == -1 es decir que la function no es un GNU pero es un builtin 
	//	(como cd, echo, pwd). hacemos todos las path y si al fin no hay mas path
	//	se sale (por el momiento, depues debe hacer la funcion get_command arriba)
	//	para hacer el builtdin (o antes)
	while ((execve(d->t[num][0], d->t[num], NULL) == -1 && pathenv[j]) || j == -1)
	{
		j++;
		i = j;
		while (pathenv[j] != ':' && pathenv[j])//vamos al fin del proxima PATH
			j++;
		ft_memset(d->t[num][0], 0, ft_strlen(d->t[num][0]));
		temp = ft_substr(pathenv, i, j - i);//apuntamos el path dentro temp
		d->t[num][0] = ft_strjoin(temp, f);// hacemos el join de path y de la funcion
	}
	printf("command not found : %s\n", f);
	return (0);
}

int	ft_exec(t_data *d, int num)
{
	pid_t	child_pid;
	char	*pathenv;

	child_pid = fork();	//	doing a fork to call execve (funcion para hacer las GNU
	if (child_pid == -1)	//	commands
	{
		printf("error fork\n");
		return (0);	//	gerer
	}
	pathenv = getenv("PATH");//	tenemos el PATH (puedes verle con "$PATH" o "env")
	if (child_pid == 0)
		cmd_execve(d, pathenv, num);	// hace la primera funcion del split
	else
		wait(0);
	return (0);
}
