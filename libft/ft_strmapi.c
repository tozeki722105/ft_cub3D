/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:04:47 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 14:41:01 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char index_toupper(unsigned int i, char c);

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		str[i] = f(i, *s++);
		i++;
	}
	return (str);
}

//int main(void)
//{
//	char s[] = "dfghjk";
//	unsigned int i;

//	i = 0;
//	printf("%s", ft_strmapi(s, index_toupper));
//	return (1);
//}

//char index_toupper(unsigned int i, char c)
//{
//	if (i % 2 == 0)
//	{
//		if ('a' <= c && c <= 'z')
//			return (c + ('A' - 'a'));
//	}
//	return (c);
//}