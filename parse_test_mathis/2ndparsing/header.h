/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:37:42 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 20:52:42 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <ctype.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_flags
{
		int	nb_pipe;
}		t_flags;

typedef struct s_data
{
		char	*input;
		char	**f;
		char	**path;
		int	nb_f;
		t_flags	flags;
}		t_data;

char	**get_path(void);

char	**split_input(t_data *d, int start, int len, int i);

int	get_nb_funcion(char *input);

void	ft_exec_funcion(t_data *d);

void	ft_echo(t_data *d, char *funcion);

void	ft_cd(t_data *d, char *funcion);

void	ft_pwd(t_data *d, char *funcion);

void	ft_export(t_data *d, char *funcion);

void	ft_unset(t_data *d, char *funcion);

void	ft_env(t_data *d, char *funcion);

void	ft_exit(t_data *d, char *funcion);

void	ft_dollar_sign(t_data *d, char *funcion);

void	ft_execve(t_data *d, char *funcion);

#endif
