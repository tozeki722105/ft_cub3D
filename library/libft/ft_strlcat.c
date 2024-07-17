/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:13:39 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 22:04:45 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_s;
	size_t	len_d;

	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	len_d = ft_strlen(dest);
	if (size < len_d)
		return (len_s + size);
	ft_strlcpy(&dest[len_d], src, size - len_d);
	return (len_d + len_s);
}

//int main(void)
//{
//	char	b[0xF] = "nyan !";
//	//char str2[] = "abcdefghij";

//	size_t n1 = ft_strlcat(b, NULL, 2);
//	//size_t n2 = strlcat(str, NULL, 2);
//	printf("%zd\n", n1);
//	//printf("%zd\n", n2);
//}