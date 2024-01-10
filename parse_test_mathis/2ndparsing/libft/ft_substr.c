/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:30 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 22:45:51 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = NULL;
	if (!s || len == 0)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (ft_strlen(s) < start)
		len = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
