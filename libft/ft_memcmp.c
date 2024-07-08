/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:34:55 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 22:23:29 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;
	size_t				i;

	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && cs1[i] == cs2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (cs1[i] - cs2[i]);
}

//int main(void)
//{
//	char	str1[30]	= "libft-test-tokyo     acdfg";
//	char	*str2		= "libft-test-tokyo     acdfg";
//	int	len = 30;

//	for (int i = 0; i <= 25; i++)
//	{
//		str2 = strndup(str1, i);

//		printf ("test%d str2 = %s\n", (i*2)+32,str2);
//		printf ("       str1 = %s\n", str1);
//		int p = memcmp(str1, str2, i);
//		int p2 = ft_memcmp(str1, str2, i);
//		printf("       size%2d: memcmp %d; ft_memcmp %3d;\n", i,p,p2);
//	}
//	return 0;
//}