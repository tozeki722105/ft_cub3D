/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_new_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:40:06 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/19 16:40:17 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "utils.h"

void	*ft_x_mlx_new_image(t_xvar *xvar, int width, int height)
{
	void	*ret;

	ret = mlx_new_image(xvar, width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_image", 1);
	return (ret);
}
