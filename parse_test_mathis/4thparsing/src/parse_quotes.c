/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:34:57 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 03:13:41 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*add_in_front(const char *arg, char *new, int start, int len)
{
	char	*dup_arg;
	char	*dup_new;

	if (len > 0 && new)
	{
		dup_arg = ft_substr(arg, start, len);
		if (!dup_arg)
			return (return_error_quotes(new));
		dup_new = ft_strdup(new);
		if (!dup_new)
		{
			free(dup_arg);
			return (return_error_quotes(new));
		}
		free(new);
		new = ft_strjoin(dup_new, dup_arg);
		free(dup_arg);
		free(dup_new);
	}
	else if (len > 0)
		new = ft_substr(arg, start, len);
	return (new);
}

char	*replace_quote(const char *arg, char *new, int *i, int nba, t_data *d)
{
	int	start;

	start = *i + 1;
	*i = ft_nxt_qte((char *)arg, *i + 1, arg[*i]);
	if (arg[*i] == 39)
		new = add_in_front(arg, new, start, *i - start);
	else
	{
		if (is_dollar((char *)arg, start))
			new = isrt_dlr_in_arg(arg, new, start + 1, nba, d);
		else
			new = add_in_front(arg, new, start, *i - start);
	}
	*i += 1;
	return (new);
}

char	*which_quote(char *arg, int i, int start, int nba, t_data *d)
{
	char	*new;

	new = NULL;
	while (arg[i])
	{
		if (arg[i] == 92 || arg[i] == 39 || arg[i] == 34)
		{
			if (i > 0)
			{
				new = add_in_front(arg, new, start, i - start);
				if (!new)
					return (NULL);
			}
			if (arg[i] == 92 && arg[i + 1])
				i++;
			else if (arg[i] == 39 || arg[i] == 34)
			{
				new = replace_quote(arg, new, &i, nba, d);
				if (!new)
					return (NULL);
			}
			start = i;
		}
		else
			i++;
	}
	new = add_in_front(arg, new, start, i - start);
	return (new);
}

char	*is_there_quote(char *arg, int nba, t_data *d)
{
	int	i;
	char	*str;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 92 || arg[i] == 39 || arg[i] == 34)
		{
			str = which_quote(arg, 0, 0, nba, d);
			free(arg);
			return (str);
		}
		i++;
	}
	return arg;
}

void	parse_quotes(t_data *d, int j)
{
	t_cmd	*first;

	first = d->cmd;
	while (d->cmd)
	{
		while (d->cmd->arg[j])
		{
			d->cmd->arg[j] = is_there_quote(d->cmd->arg[j], j, d);
			if (!d->cmd->arg[j])
			{
				while (d->cmd->arg[j + 1])
				{
					free(d->cmd->arg[j + 1]);
					j++;
				}
				return ;
			}
			j++;
		}
		free(d->cmd->exe);
		d->cmd->exe = d->cmd->arg[0];
		d->cmd = d->cmd->next;
	}
	d->cmd = first;
}
