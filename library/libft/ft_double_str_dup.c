/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_str_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:27:07 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:27:08 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_double_str_dup(char **d_str)
{
	char **res;
	size_t	i;
	size_t	y_count;

	y_count = ft_count_rows(d_str);
	res = (char **)malloc((y_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < y_count)
	{
		res[i] = ft_strdup(d_str[i]);
		if (!res[i])
		{
			ft_free_double_str(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}