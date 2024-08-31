/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_xpm_file_to_image.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:38:21 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/31 04:38:30 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "utils.h"

#if defined(__linux__)

void	*ft_x_mlx_xpm_file_to_image(t_xvar *xvar, char *filename, int *width,
		int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(xvar, filename, width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_xpm_file_to_image error", 1);
	return (ret);
}
#else

void	*ft_x_mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width,
		int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_xpm_file_to_image error", 1);
	return (ret);
}

#endif
