#include "ogv1.h"
#include "calc.h"

t_pos calc_horizontal_start(t_mlx *mlx, double ray_angle)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_pos pos;

	if (is_up(ray_angle))
		pos.y = ((int)player.y / map.panel_side) * map.panel_side - map.panel_side ;
	else
		pos.y = (((int)player.y / map.panel_side) * map.panel_side)  ;
	pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));

	pos.y = pos.y - player.y;
	pos.x = pos.x - player.x;
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

t_pos	calc_horizontal_inter(t_mlx *mlx, double ray_angle, t_pos *f_pos)
{
	t_map map;
	t_player player;
	int step;
	t_pos pos;

	map = mlx->map;
	player = mlx->player;
	step = abs(map.panel_side/f_pos->y);
	pos.x = player.x;
	pos.y = player.y;
	int diff =0;
	if (is_up(ray_angle))
		diff = -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if (map.data[pos.y / map.panel_side + diff ][pos.x / map.panel_side ] == '1')
			return (pos);
		pos.y += f_pos->y * step;
		pos.x += f_pos->x * step;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos *find2_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;
	t_pos f_pos;

	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	f_pos = calc_horizontal_start(mlx, ray_angle);//pos(274,200)
	// display_horizontal_grid_inter(mlx, ray_angle, *pos, GREEN);
	*pos = calc_horizontal_inter(mlx, ray_angle, &f_pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}
