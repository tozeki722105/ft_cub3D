#include "ogv1.h"
#include "calc.h"
#include "config.h"

void draw_wall(t_mlx *mlx, int start);

int	pick_src(int src_x, t_src src, t_intersection inter, int y)
{
	int len = (src.height * y) / inter.wall_height;
	// return (src.buffer[len][src_x]);
	return (pick_color(&src, src_x, len));
}

t_src get_img(t_mlx *mlx, t_intersection intersection)
{
	if (intersection.touching_axis == HORIZONTAL)
	{
		if (is_up(intersection.degree))
			return (mlx->textures.north);
		else
			return (mlx->textures.south);
	}
	else
	{
		if (is_right(intersection.degree))
			return (mlx->textures.east);
		else
			return (mlx->textures.west);
	}
}

int calc_src_x(t_intersection inter, int x, t_mlx *mlx, t_src src)
{
	if (inter.touching_axis == HORIZONTAL)
	{
		if (is_up(inter.degree))
			return (src.width * (int)abs(inter.origin_offset - inter.x) / mlx->map.panel_side);
		else
			return (src.width * (int)abs(inter.origin_offset - inter.x) / mlx->map.panel_side);
	}
	else
	{
		if (is_right(inter.degree))
			return (src.height * (int)abs(inter.origin_offset - inter.y) / mlx->map.panel_side);
		else
			return (src.height * (int)abs(inter.origin_offset - inter.y) / mlx->map.panel_side);
	}
}

void draw_vertical_line_of_object(t_intersection intersection, int x, t_mlx *mlx)
{
	int y;
	int i;
	t_src src = get_img(mlx, intersection);

	y = (WINDOW_HEIGHT / 2) - ((int)intersection.wall_height / 2);
	int src_x = calc_src_x(intersection, x, mlx, src);
	i = 0;
	while (i < (int)intersection.wall_height)
	{
		put_pixel(&(mlx->img), x, y, pick_src(src_x, src, intersection, i));
		y++;
		i++;
	}
}

void draw_wall(t_mlx *mlx, int start)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_img img = mlx->img;
	double draw_angle_step;
	double draw_start_angle;
	int i;

	draw_start_angle = fix_angle(player.angle + (FOV / 2));
	draw_angle_step = (double)FOV / ((double)WINDOW_WIDTH / 2);
	i = start;
	while (i < WINDOW_WIDTH)
	{
		t_intersection res = calc_intersection(mlx, draw_start_angle);
		draw_vertical_line_of_object(res, i, mlx);
		draw_start_angle = fix_angle(draw_start_angle - draw_angle_step);
		i++;
	}
}
