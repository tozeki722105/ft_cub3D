/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_strdup_padd_space.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:22:13 by toshi             #+#    #+#             */
/*   Updated: 2024/08/28 22:23:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char *double_strdup_padd_space_helper(char *str, size_t x_count, bool padding_flag)
{
	char *res;

	res = (char *)ft_x_malloc((x_count + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memset(res, ' ', x_count);
	res[x_count] = '\0';
	if (!padding_flag)
		ft_memmove(res + sizeof(char), str, ft_strlen(str));
	return (res);
}

char	**double_strdup_padd_space(char **d_str)
{
	char	**res;
	size_t	i;
	size_t	y_count;
	size_t 	x_count;

	y_count = ft_count_rows(d_str) + 2;
	res = (char **)ft_x_malloc((y_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	x_count = ft_strlen(*d_str) + 2;
	i = 0;
	while (i < y_count)
	{
		res[i] = double_strdup_padd_space_helper(*d_str, 
			x_count, (i == 0 || i == y_count - 1));
		if (!res[i])
		{
			ft_free_double_str(res);
			return (NULL);
		}
		d_str += !(i == 0 || i == y_count - 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}