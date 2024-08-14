/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:20:51 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/14 15:08:21 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_ceiling_floor(t_mlx *mlx, int ceiling_color, int floor_color)
{
	size_t	half_height;
	size_t	y;
	size_t	x;

	half_height = WINDOW_HEIGHT / 2;
	y = 0;
	while (y < half_height)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			put_pixel(&(mlx->img), x++, y, ceiling_color);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			put_pixel(&(mlx->img), x++, y, floor_color);
		y++;
	}
}

void	draw_background(t_mlx *mlx, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			put_pixel(&(mlx->img), x++, y, color);
		y++;
	}
}
