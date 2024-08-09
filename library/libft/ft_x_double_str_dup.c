/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_double_str_dup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:25 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:52:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//malloc失敗したら、exitするだけのft_strtrim
//s1がNULLのときの対応追加
char **ft_x_double_str_dup(char **d_str)
{
	char	**res;

	if (!d_str)
		return (NULL);
	res = ft_double_str_dup(d_str);
	if (!res)
		ft_my_perror_exit("malloc", 1);
	return (res);
}