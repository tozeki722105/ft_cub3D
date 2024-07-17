/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:34:03 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 21:21:49 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	size_t	len;

	cc = (char) c;
	len = ft_strlen(s);
	while (len > 0 && s[len] != cc)
		len--;
	if (s[len] != cc)
		return (NULL);
	else
		return ((char *)&s[len]);
}

//int main (void)
//{
//	char str[] = "a123456789";
//	char c = '\0';

//	char *s = ft_strrchr(str, c);
//	if (s == NULL)
//		printf("out");
//	else
//		printf("%s", s);
//}