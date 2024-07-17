/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:33:10 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 22:22:35 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*cbuf;
	unsigned char	cch;
	size_t			i;

	cbuf = (unsigned char *)buf;
	cch = (unsigned char)ch;
	i = 0;
	while (i < n)
	{
		cbuf[i] = cch;
		i++;
	}
	return (buf);
}

//int main(void)
//{
//	char str[] = "abcdefghijk";

//	ft_memset(&str[2], '*', 3);
//	printf("%s\n", str);

//	return (0);

//}