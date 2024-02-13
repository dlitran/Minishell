/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:45:21 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/12 23:32:52 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*simple_quote(char *str, int *i)
{
	(void)str;
	(void)i;
	printf("simple_quotes\n");
	*i = ft_go_next_quote(str, *i, 39);
	return (NULL);
}

char	*double_quote(char *str, char *cmd, int *i)
{
	int	start;
	char	*new;
	char	*sub;

	start = *i + 1;
	*i = ft_go_next_quote(cmd, *i, 34) + 1;
	sub = ft_substr(cmd, start, *i - start - 1);
	if (!sub)
	{
		free(str);
		return (NULL);
	}
	if (str)
	{
		new = ft_strjoin(str, sub);
		free(str);
	}
	else
		new = ft_strdup(sub);
	if (!new)
		return (NULL);
	free(sub);
	return (new);
}

void	parse_quotes(t_data *d)
{
	int	i;
	int	start;
	int	j;
	int	indice;
	char	*new;
	char	c;
	char	*dup;
	char	*str;
	t_cmd	*first;

	first = d->cmd;
	while (d->cmd)
	{
		j = 0;
		while (d->cmd->arg[j])
		{
			i = 0;
			str = NULL;
			while (d->cmd->arg[j][i])
			{
				start = i;
				c = d->cmd->arg[j][i];
				indice = 1;
				if (c == 92 || c == 39 || c == 34)
				{
					indice = 0;
					if (i > 0)
					{
						new = ft_substr(d->cmd->arg[j], start, start - i);
						if (!new)
						{
							if (str)
								free(str);
							return ;//protect
						}
						if (str)
						{
							dup = ft_strdup(str);
							free(str);
						}
						str = ft_strjoin(dup, new);
						free(new);
						if (!str)
						{
							return ;//protect
						}
					}
					if (c == 92 && d->cmd->arg[j][i + 1])
					{
						i++;
						new = ft_substr(str, i, 1);
						if (!new)
						{
							if (str)
								free(str);
							return ;//protect
						}
						str = ft_strjoin(str, new);
						free(new);
					}
					else if (c == 39)
						str = simple_quote(d->cmd->arg[j], &i);
					else if (c == 34)
						str = double_quote(str, d->cmd->arg[j], &i);
				}
				printf("i = %d\n", i);
				i++;
			}
			if (indice == 1)
			{
				dup = ft_strdup(str);
				new = ft_substr(d->cmd->arg[j], start, start - i);
				free(str);
				str = ft_strjoin(dup, new);
			}
			if (str)
			{
				free(d->cmd->arg[j]);
				d->cmd->arg[j] = ft_strdup(str);
				free(str);
			}
			printf("d->cmd->arg[j] = $%s$\n", d->cmd->arg[j]);
			j++;
		}
		free(d->cmd->exe);
		d->cmd->exe = d->cmd->arg[0];
		d->cmd = d->cmd->next;
	}
	d->cmd = first;
}
