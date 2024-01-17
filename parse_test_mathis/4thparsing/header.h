/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:29:43 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/17 01:40:24 by mafranco         ###   ########.fr       */
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

typedef struct s_cmd
{
	struct s_cmd	*next;
	char	*exe;
	char	**arg;
	int	nb_arg;
	int	pipe;
	int	inferior;	//	<
	int	inferior_two;	//	<<
	int	superior;	//	>
	int	superior_two;	//	>>
}		t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	t_cmd	*first;
	char	**env;
	char	*path;
	int	nb_f;
}		t_data;


/*	error_manager.c		*/

int	error_msg(char *str);



/*	free_data.c		*/

void	free_commands(t_data *d, char *input);

void	free_data(t_data *d);

int	free_newcmd_parsing(t_data *d, t_cmd *cmd);

int	free_cmd_parsing(t_data *d, t_cmd *cmd);


/*	ft_getenv.c		*/

int	ft_getenv(t_data *d, char **envp);

/*	pipe.c			*/

int	check_pipe(char *input);

/*	redir.c			*/

int	check_redir(char *input);

/*	quotes.c		*/

int	ft_go_next_quote(char *input, int i, char quote);

int	check_quotes(char *input);

/*	ft_parse_input.c	*/

int	ft_parse_input(char *input, t_data *d);

/*	utils_parse.c		*/

void	free_arg(char **arg, int k);

t_cmd	*ft_new_cmd(void);

void	get_redirection(char *input, int *i, t_data *d);

void	get_nb_arg(char *input, int i, t_data *d);

/*	utils.c		*/

int	ft_is_blank(char *input);

int	ft_go_next_space(char *input, int i);

int	ft_skip_space(char *input, int i);

#endif
