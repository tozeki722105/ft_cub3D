#include "calc.h"
#include "ogv1.h"

t_pos calc_ver_start(t_mlx *mlx, double ray_angle)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_pos pos;
	int panel_origin_x;
	
	panel_origin_x = ((int)(player.x / map.panel_side) * map.panel_side);
	if (player.x == panel_origin_x || !is_right(ray_angle)) //
		pos.x = panel_origin_x; // - BOUND_ADJUSTMENT
	else
		pos.x = panel_origin_x + map.panel_side;
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
	int flag;

	map = mlx->map;
	player = mlx->player;
	step = map.panel_side;
	flag = 0;
	if (!is_right(ray_angle))
	{
		flag = 1;//
		step *= -1;
	}
	while (pos.x < map.width && pos.x > 0 && pos.y > 0 && pos.y < map.height)
	{
		// printf("%d %d %d\n", pos.y, (pos.y / map.panel_side), (pos.x / map.panel_side) - flag);
		if (map.data[(pos.y / map.panel_side)][(pos.x / map.panel_side) - flag] == '1')
			return (pos);
		pos.x += step;
		pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos *search_vertical_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;

	// printf("start\n");
	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	*pos = calc_ver_start(mlx, ray_angle);
	// display_ver_grid_inter(mlx, ray_angle, *pos, GREEN);
	*pos = calc_ver_inter(mlx, ray_angle, *pos);
	// draw_rect_safely(mlx, *pos, 10, RED);
	// printf("end\n");
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}
	// draw_rect_safely(mlx, *pos, 10, RED);
	// if (pos->x > 0 && pos->x < mlx->map.width && pos->y > 0 && pos->y < mlx->map.height)
	// 	draw_line(&(mlx->img), pos->x, pos->y, mlx->player.x, mlx->player.y, RED);