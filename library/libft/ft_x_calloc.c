/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:22 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:52:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_x_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count == 0 || size == 0 || size > SIZE_MAX / count)
		return (NULL);
	ret = ft_calloc(count, size);
	if (ret == NULL)
		ft_my_perror_exit("malloc", 1);
	return (ret);
}