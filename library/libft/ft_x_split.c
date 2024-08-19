/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:39 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:08:14 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ここのNULLリターンは必要か審議->make_cmdで必要
char	**ft_x_split(const char *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = ft_split(s, c);
	if (!strs)
		ft_my_perror_exit("malloc", 1);
	return (strs);
}
