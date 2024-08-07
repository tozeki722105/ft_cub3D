/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:32 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:25:32 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_x_malloc(size_t size)
{
	void	*ret;

	if (size == 0)
		return (NULL);
	ret = (void *)malloc(size);
	if (ret == NULL)
		ft_my_perror_exit("malloc", 1);
	return (ret);
}