/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:51:44 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 14:40:48 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void index_toupper(unsigned int i, char *c)
//{
//	if (i % 2 == 0)
//	{
//		if ('a' <= *c && *c <= 'z')
//			*c += ('A' - 'a');
//	};
//}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (*s)
	{
		f(i++, s++);
	}
}

//int main(void)
//{
//	char s[] = "dfghjk";

//	ft_striteri(s, index_toupper);
//	printf("%s", s);
//	return (1);
//}