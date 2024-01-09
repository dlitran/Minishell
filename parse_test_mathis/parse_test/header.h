/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:37:42 by mafranco          #+#    #+#             */
/*   Updated: 2023/11/28 21:03:17 by mafranco         ###   ########.fr       */
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

typedef struct s_data
{
		char	*input;
		char	***t;
		int	nb_f;
}		t_data;

void	*freeall(char ***table, int i);

int	ft_parse(t_data *d);

int	is_special(char *str);

int	get_nb_function(char *str);

char	***max_split(t_data *d);

size_t	find_redirection(char *str, size_t len);

int	ft_exec(t_data *d, int num);

int	get_command(char *str);

#endif
