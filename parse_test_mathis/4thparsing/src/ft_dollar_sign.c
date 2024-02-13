/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:42 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/13 21:51:36 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*return_error_dollar(char *new)
{
	if (new)
		free(new);
	perror("error allcoating memory for dollar insertion");
	return (NULL);
}

char	*add_in_front2(char *arg, char *new, int start, int len)
{
	char	*dup_arg;
	char	*dup_new;

	if (len > 0 && new)
	{
		dup_arg = ft_substr(arg, start, len);
		if (!dup_arg)
			return (return_error_dollar(new));
		dup_new = ft_strdup(new);
		if (!dup_new)
		{
			free(dup_arg);
			return (return_error_dollar(new));
		}
		free(new);
		new = ft_strjoin(dup_new, dup_arg);
		free(dup_arg);
		free(dup_new);
	}
	else if (len > 0)
		new = ft_substr(arg, start, len);
	free(arg);
	return (new);
}

char	*get_dlr(char *arg, char *new, int *i, t_data *d)
{
	char	*dlr;
	int		cpi;
	int		j;

	cpi = *i;
	*i = find_next_space(arg, *i + 1);
	dlr = ft_substr(arg, cpi + 1, *i - cpi - 1);
	if (!dlr)
		return (NULL);
	j = 0;
	while (d->env[j])
	{
		if (ft_strncmp(d->env[j], dlr, ft_strlen(dlr)) == 0)
		{
			new = add_in_front(d->env[j], new, ft_strlen(dlr) + 1,
					ft_strlen(d->env[j]) - ft_strlen(dlr) - 1);
			if (!new)
				return (return_error_dollar(dlr));
		}
		j++;
	}
	free(dlr);
	return (new);
}

char	*ft_dollar_sign(char *arg, int i, int start, t_data *d)
{
	char	*new;

	new = NULL;
	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
			i = ft_nxt_qte(arg, i + 1, arg[i]);
		if (arg[i] == '$')
		{
			if (i > 0)
			{
				new = add_in_front(arg, new, start, i - start);
				if (!new)
					return (return_error_dollar(arg));
			}
			new = get_dlr(arg, new, &i, d);
			start = i;
			if (!new)
				return (return_error_dollar(arg));
		}
		else
			i++;
	}
	new = add_in_front2(arg, new, start, i - start);
	return (new);
}
