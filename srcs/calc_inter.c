#include "ogv1.h"
#include "calc.h"

//移動させても良い
//t_pos pos = t_inter.pos
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

	pos.y = pos.y - player.y ;
	pos.x = pos.x - player.x ;
	return (pos);
}

//移動させても良い
/* void	display_ver_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color) */
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
	double step;
	t_pos pos;

	map = mlx->map;
	player = mlx->player;
	step = fabs((double)(map.panel_side)/f_pos->x); 
	/* step = abs(map.panel_side/f_pos->x) - BOUND_ADJUSTMENT; */
	pos.x = player.x + f_pos -> x;
	pos.y = player.y + f_pos ->y;
	int diff = 0;
	if (is_right(ray_angle))
		diff = 1;
	while (pos.x <= map.width && pos.x >= 0 
		&& pos.y >= 0 && pos.y <= map.height)
	{
		if(map.data[pos.y / map.panel_side ][pos.x / map.panel_side] == '1')
			return (pos);
		pos.x += f_pos->x * step;
		pos.y += f_pos->y * step;
	}
	printf("no pos\n");
	if(pos.x < 0)
		pos.x = 0;
	if(pos.y < 0)
		pos.y = 0;
	return (pos);
}

#include <math.h>
t_pos *find_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;
	t_pos f_pos;

	/* if ((int)ray_angle == 90 || (int)ray_angle == 270) */
	/* 	return (NULL); */
	f_pos = calc_ver_start(mlx, ray_angle);//pos(300,148)
	if(f_pos.x == 0 || f_pos.y == 0)
	{
			printf("no pos\n");
			return(NULL);
	}
	pos = (t_pos *)malloc(sizeof(t_pos));
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

	v_inter = find_calc_inter(mlx, ray_angle);//x =300,y=148
	h_inter = find2_calc_inter(mlx, ray_angle);//x =324,y =99
	if(!v_inter)
		draw_rect_safely(mlx, *v_inter, 10, BLUE);
	if(!h_inter)
		draw_rect_safely(mlx, *h_inter, 10, RED);
}
