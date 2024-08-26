/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_new_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:40:06 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 14:35:31 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "utils.h"

#if defined(__linux__)

void	*ft_x_mlx_new_image(t_xvar *xvar, int width, int height)
{
	void	*ret;

	ret = mlx_new_image(xvar, width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_image error", 1);
	return (ret);
}
#else

void	*ft_x_mlx_new_image(void *mlx_ptr, int width, int height)
{
	void	*ret;

	ret = mlx_new_image(mlx_ptr, width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_image error", 1);
	return (ret);
}
#endif