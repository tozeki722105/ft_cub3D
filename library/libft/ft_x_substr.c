/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_substr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:26:03 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:52:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//malloc失敗したら、exitするだけのft_substr
//ここのNULLリターンは必要か審議->今のところs=NULLのパターンはない
char	*ft_x_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = ft_substr(s, start, len);
	if (!str)
		ft_my_perror_exit("malloc", 1);
	return (str);
}