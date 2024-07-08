/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:33:40 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 22:23:50 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	while (i + 1 < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

//int main(void)
//{
//	char str[10] = "fghj";
//	char *src = NULL;
//	int n = 10;
//	size_t i;
//	size_t i2;

//	i = strlcpy(str, src, n);
//	printf("ft  %lu\n", i);
//	i2 = ft_strlcpy(str, src, n);
//	printf("str %lu\n", i2);
//}