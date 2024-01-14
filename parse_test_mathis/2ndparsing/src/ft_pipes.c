/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:17:02 by dlitran           #+#    #+#             */
/*   Updated: 2024/01/12 15:17:02 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_pipes(char	*cmd1, char *cmd2, char **envp)
{
	pid_t	pid;
	int	fd[2];
	char const *arg1[2];
	char const *arg2[3];

	arg1[0] = "ls";
	arg1[1] = NULL;
	arg2[0] = "grep";
	arg2[1] = "minishell";
	arg2[2] = NULL;

	(void)cmd1;
	(void)cmd2;
	if (pipe(fd) == -1)
		return ;
	printf("%i, %i\n", fd[0], fd[1]);
	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		return;
	}
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO); // stdout becomes fd[1](write extreme), buffered on the kernel until is read.
		execve("/usr/bin/ls", (char *const*)arg1, envp);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	execve("/usr/bin/grep", (char *const*)arg2, envp);
	printf("fisnished\n");
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_pipes("/usr/bin/ls", "/usr/bin/grep", envp);
	//execve("/usr/bin/ls", argv, envp);
	return (0);
}
