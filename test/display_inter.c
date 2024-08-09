#include "calc.h"

static void	display_horizontal_grid_inter_pos(t_mlx *mlx, double ray_angle, t_pos pos, int color)
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
		draw_square_center_safely(mlx, pos, 10, color);
		pos.y += step;
		pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	}
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