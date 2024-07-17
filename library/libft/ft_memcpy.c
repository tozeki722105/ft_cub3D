/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:28:59 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 15:10:13 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;
	size_t				i;

	if (dest == src)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

//int main(void)
//{
//	char str[] = "abcdefghij";
//	char str2[] = "abcdefghij";

//	printf("1; %s\n", (char *)memcpy(NULL, NULL, 4));
//	printf("2; %s\n", (char *)ft_memcpy(NULL, NULL, 4));

//	return (0);
//}