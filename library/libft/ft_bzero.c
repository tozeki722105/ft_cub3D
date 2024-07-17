/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:29:22 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/01 22:04:51 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *buf, size_t n)
{
	return (ft_memset(buf, '\0', n));
}

//int main(void)
//{
//	char str[] = "abcdefghijk";

//	ft_bzero(&str[3], 2);
//	printf("%s\n", str);

//	return (0);

//}