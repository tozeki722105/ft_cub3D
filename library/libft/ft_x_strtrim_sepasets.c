/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_strtrim_sepasets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:50 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:11:48 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_x_strtrim_sepasets(const char *s1, const char *front_trim_set,
		const char *back_trim_set)
{
	char	*trimed_str;

	if (s1 == NULL)
		return (NULL);
	if (front_trim_set == NULL && back_trim_set == NULL)
		return ((char *)s1);
	trimed_str = ft_strtrim_sepasets(s1, front_trim_set, back_trim_set);
	if (!trimed_str)
		ft_my_perror_exit("malloc", 1);
	return (trimed_str);
}
