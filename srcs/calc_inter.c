#include "ogv1.h"
#include "calc.h"

void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color)
{
	if (pos.x < (mlx->map.x_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2))
		&& pos.x > (rect_size / 2) + (rect_size % 2)
		&& pos.y > (rect_size / 2) + (rect_size % 2)
		&& pos.y < (mlx->map.y_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2)))
		draw_rect(&(mlx->img), pos.x - (rect_size / 2), pos.y - (rect_size / 2), rect_size, rect_size, color);
}

t_pos calc_ver_start(t_mlx *mlx, double ray_angle)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_pos pos;

	if (is_right(ray_angle))
		pos.x = ((int)(player.x / map.panel_side) * map.panel_side) + map.panel_side;
	else
		pos.x = ((int)(player.x / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	return (pos);
}

void	display_ver_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color)
{
	t_map map;
	t_player player;
	int step;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	if (!is_right(ray_angle))
		step *= -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		// printf("x=%d,y=%d  ", (int)pos.x, (int)pos.y);
		draw_rect_safely(mlx, pos, 10, color);
		pos.x += step;
		pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	}
	// printf("\n");
}

t_pos	calc_ver_inter(t_mlx *mlx, double ray_angle, t_pos pos)
{
	t_map map;
	t_player player;
	int step;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	if (!is_right(ray_angle))
		step *= -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
			return (pos);
		pos.x += step;
		pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}


t_pos *find_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;

	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	*pos = calc_ver_start(mlx, ray_angle);
	// display_ver_grid_inter(mlx, ray_angle, pos, GREEN);
	*pos = calc_ver_inter(mlx, ray_angle, *pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}

void calc_test(t_mlx *mlx, double ray_angle)
{
	t_pos *v_inter;
	t_pos *h_inter;

	v_inter = find_calc_inter(mlx, ray_angle);
	h_inter = find2_calc_inter(mlx, ray_angle);
}
