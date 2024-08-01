#include "ogv1.h"
#include "calc.h"
#include "config.h"

/// @brief use calc_origin
int calc_img_x(t_inter inter, t_src img, int map_panel_side)
{
	int img_offset;
	
	if (inter.axis == HORIZONTAL)
		img_offset = (int)fabs((double)(inter.origin_offset - inter.pos.x));
	else
		img_offset = (int)fabs((double)(inter.origin_offset - inter.pos.y));
	return ((img.width * img_offset) / map_panel_side);
}


t_src get_img(t_mlx *mlx, t_inter inter)
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

void draw_vertical_line_of_wall(t_mlx *mlx, t_inter inter, size_t put_x)
{
	int put_y;
	size_t wall_i;
	size_t img_x;
	size_t img_y;
	t_src img;

	img = get_img(mlx, inter);
	// img_x = (img.width * inter.origin_offset) / mlx->map.panel_side;
	img_x = calc_img_x(inter, img, mlx->map.panel_side);
	put_y = (WINDOW_HEIGHT / 2) - ((int)inter.wall_height / 2);
	wall_i = 0;
	while (wall_i < (int)inter.wall_height)
	{

		if (put_y >= 0 && put_y < WINDOW_HEIGHT)
		{
			img_y = (img.height * wall_i) / inter.wall_height;
			put_pixel(&(mlx->img), put_x, put_y, pick_color(&img, img_x, img_y));
		}
		put_y++;
		wall_i++;
	}
}

/// @brief If you call this function from the coordinates of a wall corner, 
///	the process never finishes. The angle is also related.
void draw_wall(t_mlx *mlx, int start)
{
	double draw_angle;
	double step;
	size_t x;
	t_inter inter;

	draw_angle = fix_angle(mlx->player.angle + (FOV / 2));
	step = (double)FOV / ((double)WINDOW_WIDTH);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		inter = new_calc_inter(mlx, draw_angle);
		// if (inter.axis == HORIZONTAL)
		// 	draw_line(&(mlx->img), mlx->player.x, mlx->player.y, inter.pos.x, inter.pos.y, RED);
		// else
		// 	draw_line(&(mlx->img), mlx->player.x, mlx->player.y, inter.pos.x, inter.pos.y, BLUE);
		draw_vertical_line_of_wall(mlx, inter, x);
		draw_angle = fix_angle(draw_angle - step);
		x++;
	}
}
