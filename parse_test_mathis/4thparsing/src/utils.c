/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:45:07 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/15 12:25:38 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


/*si no es espacio, si es un " o ' se vas al " o ' despues. si se encuentra
  una redirection, se sale*/
int	ft_go_next_space(char *input, int i)
{
	while (input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
		&& input[i] != '\v' && input[i] != '\f' && input[i] != '\r'
		&& input[i])
	{
		if (input[i] == 92 && input[i + 1])
			i++;
		else if (input[i] == 34 || input[i] == 39)
			i = ft_go_next_quote(input, i, input[i]);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int	ft_nxt_qte(char *input, int i, char quote)
{
	while (input[i])
	{
		if (input[i] == quote)
			return (i);
		i++;
	}
	return (i);
}

int	ft_skip_space(char *input, int i)
{
	while ((input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'
		|| input[i] < 0) && input[i])
		i++;
	return (i);
}

int	ft_is_blank(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '\t' && input[i] != '\n' && input[i] != '\v'
			&& input[i] != '\f' && input[i] != '\r'
			&& input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}


char	*ft_strjoin_gnl(char *s1, char *s2, size_t len)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*join;

	s1_size = ft_strlen(s1);
	s2_size = len;
	join = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_size);
	ft_strlcpy(join + s1_size, s2, s2_size);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[1000 + 1];
	char		*line;
	char		*newline;
	int			bytes;
	int			tocopy;

	line = ft_strup(buf);
	while(!ft_strchr(line, '\n') && (bytes = read(fd, buf, 1000)) > 0)
	{
		buf[bytes] = '\0';
		line = ft_strjoin_gnl(line, buf, bytes);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	if (newline)
	{
		tocopy = newline - line + 1;
		ft_strlcpy(buf, newline + 1, 1000);
	}
	else
	{
		tocopy = ft_strlen(line);
		ft_strlcpy(buf, "", 1000);
	}
	line[tocopy] = '\0';
	return (line);
}
