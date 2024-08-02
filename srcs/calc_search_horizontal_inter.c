#include "calc.h"
#include "ogv1.h"

t_pos calc_hori_start(t_mlx *mlx, double ray_angle)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_pos pos;
	int panel_origin_y;

	panel_origin_y = ((int)player.pos.y / map.panel_side) * map.panel_side;
	if (player.pos.y == panel_origin_y || is_up(ray_angle))
		pos.y = (panel_origin_y) ;//- BOUND_ADJUSTMENT
	else
		pos.y = (panel_origin_y) + map.panel_side;
	pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	return (pos);
}

void	display_hori_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color)
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
		// printf("x=%d,y=%d  ", (int)pos.x, (int)pos.y);
		draw_rect_safely(mlx, pos, 10, color);
		pos.y += step;
		pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	}
	// printf("\n");
}

t_pos	calc_hori_inter(t_mlx *mlx, double ray_angle, t_pos pos)
{
	t_map map;
	t_player player;
	int step;
	int flag;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	flag = 0;
	if (is_up(ray_angle))
	{
		flag = 1;
		step *= -1;
	}
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if (map.data[((int)pos.y / map.panel_side)-flag][(int)pos.x / map.panel_side] == '1')
			return (pos);
		pos.y += step;
		pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos *search_horizontal_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;

	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	*pos = calc_hori_start(mlx, ray_angle);
	// display_ver_grid_inter(mlx, ray_angle, pos, GREEN);
	*pos = calc_hori_inter(mlx, ray_angle, *pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}