/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:33:33 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/16 19:56:05 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		return (0);
	else
		return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

//int main (void)
//{
//	char str[] = "--";
//	char str2= -128;
//	//char str2= -42;
//	int n = 3;
//	printf("%d\n", strncmp(str, &str2, n));
//	printf("%d\n", ft_strncmp(str, &str2, n));
//}