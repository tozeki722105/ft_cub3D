/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:43 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:25:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//malloc失敗したら、exitするだけのft_strtrim
//s1がNULLのときの対応追加
char	*ft_x_strdup(const char *s1)
{
	char	*str;

	if (!s1)
		return (NULL);
	str = ft_strdup(s1);
	if (!str)
		ft_my_perror_exit("malloc", 1);
	return (str);
}