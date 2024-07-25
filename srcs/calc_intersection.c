#include "ogv1.h"
#include "calc.h"

double calc_distance(double ray_angle, t_player player, t_intersection res)
{
	return (cos_wrap(ray_angle) * (res.x - player.x) - sin_wrap(ray_angle) * (res.y - player.y));
}

double calc_offset(double ray_angle, enum e_axis axis, t_intersection inter, t_map map, t_mlx *mlx)
{
	double res;
	if (axis == HORIZONTAL)
	{
		if (is_up(ray_angle))
			return (((int)inter.x / map.panel_side) * map.panel_side);
		else
			return (((int)inter.x / map.panel_side) * map.panel_side) + map.panel_side;
	}
	else
	{
		if (is_right(ray_angle))
			return (((int)inter.y / map.panel_side) * map.panel_side);
		else
			return (((int)inter.y / map.panel_side) * map.panel_side) + map.panel_side;
	}
}

int get_vartical_first(t_mlx *mlx, int *pos_y, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x;
	if (is_right(ray_angle))
		pos_x = (((int)player.x / map.panel_side) * map.panel_side) + map.panel_side;
	else
		pos_x = (((int)player.x / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	*pos_y = player.y - ((pos_x - player.x) * tan_wrap(ray_angle));
	// draw_rect(&(mlx->img), pos_x-5, *pos_y-5, 10, 10, SKY);
	return (pos_x);
}

int		get_horizontal_first(t_mlx *mlx, int *pos_y, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int pos_x = 0;
	if (is_up(ray_angle))
		*pos_y = (((int)player.y / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	else
		*pos_y = (((int)player.y / map.panel_side) * map.panel_side) + map.panel_side;
	pos_x = player.x + ((player.y - *pos_y) * cot_wrap(ray_angle));
	return (pos_x);
}

void	display_vartical_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	int add = map.panel_side;
	if (!is_right(ray_angle))
		add *= -1;
	while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
	{
		draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
		// printf("[%d][%d] ", pos.y / map.panel_side, pos.x / map.panel_side);
		pos.x += add;
		pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	}
	// printf("\n");
}

void display_horizontal_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.y_count * map.panel_side;
	int add = map.panel_side;
	if (is_up(ray_angle))
		add *= -1;
	while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
	{
		draw_rect(&(mlx->img), pos.x-5, pos.y-5, 10, 10, color);
		pos.y += add;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
}

t_intersection display_vertical_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	int add = map.panel_side;
	t_intersection res;
	if (!is_right(ray_angle))
		add *= -1;
	while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			res.touching_axis = VERTICAL;
			res.x = pos.x;
			res.y = pos.y;
			res.degree = ray_angle;
			res.distance = calc_distance(ray_angle, player, res);
			res.origin_offset = calc_offset(ray_angle, res.touching_axis, pos, map, mlx);
			return (res);
		}
		pos.x += add;
		pos.y = player.y + ((player.x - pos.x) * tan_wrap(ray_angle));
	}
	return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
}

t_intersection display_horizontal_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	t_intersection res;
	int end = map.y_count * map.panel_side;
	int add = map.panel_side;
	if (is_up(ray_angle))
		add *= -1;
	while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			res.touching_axis = HORIZONTAL;
			res.x = pos.x;
			res.y = pos.y;
			res.degree = ray_angle;
			res.distance = calc_distance(ray_angle, player, res);
			res.origin_offset = calc_offset(ray_angle, res.touching_axis, pos, map, mlx);
			return (res);
		}
		pos.y += add;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
	return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
}

t_intersection	find_vartical_intersection(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_intersection first;
	
	player = mlx->player;
	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
	first.x = get_vartical_first(mlx, &(first.y), ray_angle);
	// display_vartical_grid_intersection(mlx, first, GREEN, ray_angle);
	return (display_vertical_intersection(mlx, first, BLUE, ray_angle));
}

t_intersection	find_horizontal_intersection(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_intersection first;
	
	player = mlx->player;
	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
	first.x = get_horizontal_first(mlx, &(first.y), ray_angle);
	// display_horizontal_grid_intersection(mlx, first, GREEN, ray_angle);
	return (display_horizontal_intersection(mlx, first, RED, ray_angle));
}

t_intersection compare_distance(t_intersection v_inter, t_intersection h_inter, t_player player, double ray_angle)
{
	if (v_inter.x == 50000)
		return (h_inter);
	if (h_inter.x == 50000)
		return (v_inter);
	if (v_inter.distance < h_inter.distance)
		return (v_inter);
	else
		return (h_inter);
}

t_intersection calc_intersection(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_map map;

	player = mlx->player;
	map = mlx->map;
	t_intersection v_inter = find_vartical_intersection(mlx, ray_angle);
	t_intersection h_inter = find_horizontal_intersection(mlx, ray_angle);
	t_intersection res = compare_distance(v_inter, h_inter, player, ray_angle);
	draw_line(&(mlx->img), player.x, player.y, res.x, res.y, WHITE);
	int ca = fix_angle(player.angle - res.degree);
	res.distance = res.distance * cos_wrap(fix_angle(player.angle - res.degree));
	res.wall_height = (WINDOW_HEIGHT * 100) / res.distance;
	return (res);
}