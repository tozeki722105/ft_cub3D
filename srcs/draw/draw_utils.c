/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:15:01 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 15:04:06 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*((int *)pixel) = color;
}

int	pick_color(t_image *img, int x, int y)
{
	char	*pixel;

	pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
	return (*((int *)pixel));
}

static void	set_value_draw_line(t_point *player, t_point *div, t_point *inter,
		t_point *direction)
{
	div->x = abs(player->x - inter->x);
	div->y = abs(player->y - inter->y);
	if (player->x < inter->x)
		direction->x = 1;
	else
		direction->x = -1;
	if (player->y < inter->y)
		direction->y = 1;
	else
		direction->y = -1;
}

void	draw_line(t_image *img, t_point player, t_point inter, int color)
{
	t_point	div;
	t_point	direction;
	int		err;
	int		e2;

	set_value_draw_line(&player, &div, &inter, &direction);
	err = div.x - div.y;
	while (1)
	{
		put_pixel(img, player.x, player.y, color);
		if (player.x == inter.x && player.y == inter.y)
			break ;
		e2 = 2 * err;
		if (e2 > -div.y)
		{
			err -= div.y;
			player.x += direction.x;
		}
		if (e2 < div.x)
		{
			err += div.x;
			player.y += direction.y;
		}
	}
}

void	draw_map(t_mlx *mlx, int floor_color, int wall_color)
{
	t_map	map;
	int	y;
	int	x;
	int		color;
	t_pos	pos;

	map = mlx->map;
	y = 0;
	while (y < map.y_count)
	{
		x = 0;
		while (x < map.x_count)
		{
			color = floor_color;
			if (map.data[y][x] == '1')
				color = wall_color;
			pos.x = (x * map.panel_side) + 1;
			pos.y = (x * map.panel_side) + 1;
			draw_square_safely(mlx, pos, map.panel_side - 2, color);
			x++;
		}
		y++;
	}
}
