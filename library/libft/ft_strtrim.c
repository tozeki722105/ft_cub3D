/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:28:31 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 13:50:05 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_start_count(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static size_t	get_end_count(const char *s1, const char *set, size_t start)
{
	size_t	len;

	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len -1]) != NULL)
		len--;
	return (len - 1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	start = get_start_count(s1, set);
	end = get_end_count(s1, set, start);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(&s1[start], 0, end - start + 1));
}
