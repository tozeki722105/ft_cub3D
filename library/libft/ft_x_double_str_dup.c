/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_double_str_dup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:25 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:07:45 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//malloc失敗したら、exitするだけのft_strtrim
//s1がNULLのときの対応追加
char	**ft_x_double_str_dup(char **d_str)
{
	char	**res;

	if (!d_str)
		return (NULL);
	res = ft_double_str_dup(d_str);
	if (!res)
		ft_my_perror_exit("malloc", 1);
	return (res);
}
