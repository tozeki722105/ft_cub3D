#include "calc.h"

static t_pos calc_vertical_start_pos(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_map map;
	t_pos pos;
	int panel_origin_x;
	
	player = mlx->player;
	map = mlx->map;
	panel_origin_x = ((int)(player.pos.x / map.panel_side) * map.panel_side);
	if (player.pos.x == panel_origin_x || !is_right(ray_angle))
		pos.x = panel_origin_x;
	else
		pos.x = panel_origin_x + map.panel_side;
	pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(ray_angle));
	return (pos);
}

static void	display_vertical_grid_inter_pos(t_mlx *mlx, double ray_angle, t_pos pos, int color)
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
		draw_square_center_safely(mlx, pos, 10, color);
		pos.x += step;
		pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(ray_angle));
	}
}

static t_pos	search_vertical_inter_pos(t_mlx *mlx, double ray_angle, t_pos pos)
{
	t_map map;
	t_player player;
	int step;
	int flag;

	map = mlx->map;
	player = mlx->player;
	flag = (!is_right(ray_angle));
	step = map.panel_side;
	if (!is_right(ray_angle))
		step *= -1;
	while (pos.x < map.width && pos.x > 0 && pos.y > 0 && pos.y < map.height)
	{
		if (map.data[((int)pos.y / map.panel_side)]
			[((int)pos.x / map.panel_side) - flag] == '1')
			return (pos);
		pos.x += step;
		pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(ray_angle));
	}
	return ((t_pos){-1, -1});
}

t_pos *calc_vertical_inter_pos(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;

	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return (NULL);
	pos = (t_pos *)ft_x_malloc(sizeof(t_pos));
	*pos = calc_vertical_start_pos(mlx, ray_angle);
	*pos = search_vertical_inter_pos(mlx, ray_angle, *pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}