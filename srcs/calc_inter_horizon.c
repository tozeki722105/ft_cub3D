#include "ogv1.h"
#include "calc.h"

t_pos calc_horizontal_start(t_mlx *mlx, double ray_angle)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_pos pos;

	if (is_up(ray_angle))
		pos.y = (((int)player.y / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	else
		pos.y = (((int)player.y / map.panel_side) * map.panel_side) + map.panel_side;
	pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	return (pos);
}

void	display_horizontal_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color)
{
	t_map map;
	t_player player;
	int step;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	if (is_up(ray_angle))
		step *= -1;
	while (pos.y > 0 && pos.y < map.height && pos.x > 0 && pos.x < map.width)
	{
		draw_rect(&(mlx->img), pos.x-5, pos.y-5, 10, 10, color);
		pos.y += step;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
}

t_pos	calc_horizontal_inter(t_mlx *mlx, double ray_angle, t_pos pos)
{
	t_map map;
	t_player player;
	int step;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	if (is_up(ray_angle))
		step *= -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
			return (pos);
		pos.y += step;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos *find2_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;

	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	*pos = calc_horizontal_start(mlx, ray_angle);
	// display_horizontal_grid_inter(mlx, ray_angle, *pos, GREEN);
	*pos = calc_horizontal_inter(mlx, ray_angle, *pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}
