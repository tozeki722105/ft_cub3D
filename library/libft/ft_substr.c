/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:20:36 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/21 22:05:06 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*str;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_strdup(""));
	if (len > len_s)
		len = len_s - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

//int main(void)
//{
//	char str[] = "libft-test-tokyo";
//	size_t size = 10;
//	//ft_substr(str, 2, 100);
//	//printf("%s\n", str);
//	printf("%s\n", ft_substr(str, 10, 5));
//}