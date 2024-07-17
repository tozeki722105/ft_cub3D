/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:19:42 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 15:14:05 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_n;
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	len_n = ft_strlen(needle);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		if (i + len_n > len)
			break ;
		if (ft_strncmp(&haystack[i], needle, len_n) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

//int main(void)
//{
//	//char *str = "";
//	char	*s1 = "MZIRIBMZIRIBMZE123";
//	char	*s2 = "MZIRIBMZE";
//	size_t	max = ft_strlen(s2);
//	printf("%s\n", ft_strnstr(s1, s2, max));
//	printf("%s\n", strnstr(s1, s2, max));

//	//printf("%20s\n", ft_strnstr(NULL, "fake", 0));
//	//printf("%20s\n", strnstr(NULL, "fake", 0));

//	//int	len = strlen(str);
//	//int test = 1;
//	//for (int i = 0; i < len; i++)
//	//{
//	//	printf("i = %d\n", i);
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "", i));
//	//	printf("%20s\n", strnstr(str, "", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "libft-test-tokyo", i));
//	//	printf("%20s\n", strnstr(str, "libft-test-tokyo", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "libft", i));
//	//	printf("%20s\n", strnstr(str, "libft", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "test", i));
//	//	printf("%20s\n", strnstr(str, "test", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "tokyo", i));
//	//	printf("%20s\n", strnstr(str, "tokyo", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "libft~", i));
//	//	printf("%20s\n", strnstr(str, "libft~", i));
//	//	test++;
//	//	printf("test%d\n", test);
//	//	printf("%20s\n", ft_strnstr(str, "z", i));
//	//	printf("%20s\n", strnstr(str, "z", i));
//	//	test++;
//	//}
//}