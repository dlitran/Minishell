/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/18 19:59:11 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

/*static char	*add_dollar(char *str, char *new, int *i, int start_a)
{
	while (str[*i] != 34)
	{
		if (str[*i] == 36)
		{
			new = add_in_front(str, new, start_a, *i - start_a);
			
		}
		*i += 1;
	}
}*/

static char	*del_simple_quotes(char *str, char *new, int *i, int start_a, t_data *d)
{
	int	start;

	(void)d;
	new = add_in_front(str, new, start_a, *i - start_a);
	*i += 1;
	start = *i;
	if (str[*i - 1] == 39)
	{
		*i = ft_go_next_quote(str, *i, str[*i - 1]);
		*i += 1;
		if (*i - 1 == start)
			return (new);
		else
			new = add_in_front(str, new, start, *i - start - 1);
	}
	//else
	//	new = add_dollar(qte->str, qte->new, i, start, d);
	return (new);
}

static char	*get_quotes(char *str, size_t len, t_data *d)
{
	(void)len;
	(void)d;
	int		i;
	int		start;
	char	*new;

	new = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (str[i + 1] != str[i])
			{
				new = del_simple_quotes(str, new, &i, start, d);
				if (!new)
					return (NULL);
			}
			else
				i += 2;
			start = i;
		}
		else
			i++;
	}
	new = add_in_front(str, new, start, i - start);
	return (new);
}

char	*ft_substr_mnsh(char const *s, unsigned int start, size_t len, t_data *d)
{
	char	*str;
	char	*new;

	str = NULL;
	new = NULL;
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (ft_strlen(s) < start)
		len = 0;
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	new = get_quotes(str, len, d);
	free(str);
	return (new);
}
