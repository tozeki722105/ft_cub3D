/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:31:42 by tozeki            #+#    #+#             */
/*   Updated: 2023/09/13 05:40:58 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	cc;
	size_t	i;

	cc = (char)c;
	i = 0;
	while (s[i] != '\0' && s[i] != cc)
		i++;
	if (s[i] != cc)
		return (NULL);
	else
		return ((char *)&s[i]);
}

//int main (void)
//{
//	char str[] = "libft-test-tokyo";
//	int c = 'l' + 256;
//	int n1 = strchr(str, c);
//	int n2 = ft_strchr(str, c);

//	printf("%p\n", str);
//	printf("%p\n", &n1);
//	printf("%p\n", &n2);

//}