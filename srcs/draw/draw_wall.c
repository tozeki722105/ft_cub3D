/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:12:37 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 14:33:44 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "config.h"
#include "main.h"

static t_image	get_img(t_mlx *mlx, t_inter inter)
{
	if (inter.axis == HORIZONTAL)
	{
		if (is_up(inter.angle))
			return (mlx->textures.north);
		else
			return (mlx->textures.south);
	}
	else
	{
		if (is_right(inter.angle))
			return (mlx->textures.east);
		else
			return (mlx->textures.west);
	}
}

static void	draw_vertical_line_of_wall(t_mlx *mlx, t_inter inter, size_t put_x)
{
	int		put_y;
	int		wall_i;
	int		img_x;
	int 	img_y;
	t_image	img;

	img = get_img(mlx, inter);
	img_x = (img.width * inter.origin_offset) / mlx->map.panel_side;
	put_y = (WINDOW_HEIGHT / 2) - ((int)inter.wall_height / 2);
	wall_i = 0;
	while (wall_i < (int)inter.wall_height)
	{
		if (put_y >= 0 && put_y < WINDOW_HEIGHT)
		{
			img_y = (img.height * wall_i) / inter.wall_height;
			if (img_y >= img.height - 4)
				img_y = img.height - 4;
			put_pixel(&(mlx->img), put_x, put_y,
				pick_color(&img, img_x, img_y));
		}
		put_y++;
		wall_i++;
	}
}

/// @brief If you call this function from the coordinates of a wall corner,
///	the process never finishes. The angle is also related.
void	draw_wall(t_mlx *mlx)
{
	double	draw_angle;
	double	step;
	size_t	x;
	t_inter	inter;

	draw_angle = fix_angle(mlx->player.angle + (FOV / 2));
	step = (double)FOV / ((double)WINDOW_WIDTH);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		inter = calc_intersection(mlx, draw_angle);
		draw_vertical_line_of_wall(mlx, inter, x);
		draw_angle = fix_angle(draw_angle - step);
		x++;
	}
}
