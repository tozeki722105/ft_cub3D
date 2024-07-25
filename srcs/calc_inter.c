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
		pos.x = ((int)(player.x / map.panel_side) * map.panel_side) + map.panel_side ;
	else
		pos.x = ((int)(player.x / map.panel_side) * map.panel_side)  ;
	pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));

	pos.y = pos.y - player.y;
	pos.x = pos.x - player.x;
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

t_pos	calc_ver_inter(t_mlx *mlx, double ray_angle, t_pos *f_pos)
{
	t_map map;
	t_player player;
	int step;
	t_pos pos;

	map = mlx->map;
	player = mlx->player;
	step = 1;
	pos.x = player.x;
	pos.y = player.y;
	if (!is_right(ray_angle))
		step = -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if(pos.y % map.panel_side )
			step = 0;
		if (map.data[pos.y / map.panel_side ][pos.x / map.panel_side + step] == '1')
			return (pos);
		pos.x += f_pos->x;
		pos.y += f_pos->y;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}


t_pos *find_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;
	t_pos f_pos;

	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return (NULL);
	pos = (t_pos *)malloc(sizeof(t_pos));
	f_pos = calc_ver_start(mlx, ray_angle);//pos(300,148)
	// display_ver_grid_inter(mlx, ray_angle, pos, GREEN);
	*pos = calc_ver_inter(mlx, ray_angle, &f_pos);
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

	//v_inter = find_calc_inter(mlx, ray_angle);//x =300,y=148
	h_inter = find2_calc_inter(mlx, ray_angle);//x =324,y =99
	//draw_rect_safely(mlx, *v_inter, 10, BLUE);
	draw_rect_safely(mlx, *h_inter, 10, RED);
}
