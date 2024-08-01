/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:55:13 by toshi             #+#    #+#             */
/*   Updated: 2024/07/18 08:36:32 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h> //malloc free

void	*ft_calloc(size_t count, size_t size)
{
	void			*str;
	size_t			i;
	unsigned char	*cstr;

	if (size == 0 || count == 0)
		return (ft_calloc(1, 1));
	else if (size > SIZE_MAX / count)
		return (NULL);
	str = (void *)malloc(size * count);
	if (str == NULL)
		return (NULL);
	cstr = (unsigned char *)str;
	i = 0;
	while (i < count)
	{
		cstr[i] = '\0';
		i++;
	}
	return (str);
}

char	*free_str_set_null(char *str)
{
	free (str);
	return (NULL);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	char	cc;
// 	size_t	i;

// 	cc = (char)c;
// 	i = 0;
// 	while (s[i] != '\0' && s[i] != cc)
// 		i++;
// 	if (s[i] != cc)
// 		return (NULL);
// 	else
// 		return ((char *)&s[i]);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_s;
	size_t	len_d;
	size_t	i;

	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	len_d = ft_strlen(dest);
	if (size < len_d)
		return (len_s + size);
	i = 0;
	while (len_d + i + 1 < size && src[i] != '\0')
	{
		dest[len_d + i] = src[i];
		i++;
	}
	dest[len_d + i] = '\0';
	return (len_d + len_s);
}
