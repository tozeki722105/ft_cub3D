/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:53:08 by tozeki            #+#    #+#             */
/*   Updated: 2024/08/08 00:52:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}

//int main (void)
//{
//	char s1[] = "where is my ";
//	char s2[] = "malloc ???";
//	//ft_strjoin(NULL, s2);
//	printf("%s", ft_strjoin(s1, s2));
//}