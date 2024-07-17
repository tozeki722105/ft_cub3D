/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:55:52 by tozeki            #+#    #+#             */
/*   Updated: 2023/10/12 20:20:48 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "string.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;
	unsigned char		cc;
	size_t				i;

	cs = (const unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n && cs[i] != cc)
		i++;
	if (i == n)
		return (NULL);
	else
		return ((void *)&cs[i]);
}

//int main(void)
//{
//	char str[] = "";
//	char *p;
//	p = ft_memchr(str, 'b', 10);
//	printf("検索文字は文字列の%ld番目\n", p);
//	return 0;
//}