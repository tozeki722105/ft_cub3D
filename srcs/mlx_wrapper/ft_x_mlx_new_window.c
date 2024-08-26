/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_new_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:37:08 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 14:35:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "utils.h"

#if defined(__linux__)

void	*ft_x_mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title)
{
	void	*ret;

	ret = mlx_new_window(xvar, size_x, size_y, title);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_window error", 1);
	return (ret);
}
#else

void	*ft_x_mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	void	*ret;

	ret = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_window error", 1);
	return (ret);
}
#endif