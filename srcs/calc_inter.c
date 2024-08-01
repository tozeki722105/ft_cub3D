#include "ogv1.h"
#include "calc.h"
#include "config.h"

static t_pos calc_v_start(t_mlx *mlx, double ray_angle)
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

static t_pos calc_v_inter(t_mlx *mlx, double ray_angle, t_pos *f_pos)
{
	t_map map;
	/* t_player player; */
	double scalar;
	t_pos pos;

	map = mlx->map;
	/* player = mlx->player; */
	scalar = fabs((double)(map.panel_side)/f_pos->x); 
	pos.x = mlx->player.x + f_pos -> x;
	pos.y = mlx->player.y + f_pos ->y;
	int diff = 0;
	if (is_right(ray_angle))
		diff = 1;
	while (pos.x <= map.width && pos.x >= 0 
		&& pos.y >= 0 && pos.y <= map.height)
	{
		if(map.data[pos.y / map.panel_side ][pos.x / map.panel_side] == '1')
			return (pos);
		pos.x += f_pos->x * scalar;
		pos.y += f_pos->y * scalar;
	}
	//grid線上の交点が見つからなかった場合(要相談)
	printf("no pos\n");
	if(pos.x < 0)
		pos.x = 0;
	if(pos.y < 0)
		pos.y = 0;
	return (pos);
}

/* static t_pos *find_calc_v_inter(t_mlx *mlx, double ray_angle) */
t_pos *find_calc_v_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;
	t_pos f_pos;

	//ray_angleのエッジケース要相談 ここでハンドリングする必要ある？
	/* if ((int)ray_angle == 90 || (int)ray_angle == 270) */
	/* 	return (NULL); */
	f_pos = calc_v_start(mlx, ray_angle);
	if(f_pos.x == 0 || f_pos.y == 0)
	{
			printf("no pos\n");
			return(NULL);
	}
	pos = (t_pos *)malloc(sizeof(t_pos));
	// display_ver_grid_inter(mlx, ray_angle, pos, GREEN);
	*pos = calc_v_inter(mlx, ray_angle, &f_pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}

double distance(t_player player,t_pos inter)
{
		double distance ;

		distance = sqrt(pow(player.x - inter.x,2.0) + pow(player.y - inter.y,2.0));
}

double calc_offset(double ray_angle, enum e_axis axis, t_pos inter, t_map map, t_mlx *mlx)
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

// void calc_test(t_mlx *mlx, double ray_angle)
t_inter calc_test(t_mlx *mlx, double ray_angle)
{
	t_inter res;
	t_pos *v_inter;
	t_pos *h_inter;

	v_inter = find_calc_v_inter(mlx, ray_angle);//x =300,y=148
	h_inter = find_calc_h_inter(mlx, ray_angle);//x =324,y =99
	if(!v_inter)
		draw_rect_safely(mlx, *v_inter, 10, BLUE);
	if(!h_inter)
		draw_rect_safely(mlx, *h_inter, 10, RED);
	if(distance(mlx->player,*v_inter) > distance(mlx->player,*h_inter))
	{
		res.pos = *h_inter;
		res.axis = HORIZONTAL;
		res.angle = ray_angle;
		res.distance = distance(mlx->player,*h_inter);
		res.origin_offset = calc_offset(ray_angle, res.axis, res.pos, mlx->map, mlx);
	}
	else
	{
		res.pos = *v_inter;
		res.axis = VERTICAL;
		res.angle = ray_angle;
		res.distance = distance(mlx->player,*v_inter);
		res.origin_offset = calc_offset(ray_angle, res.axis, res.pos, mlx->map, mlx);
	}
	//t_inter res = compare_distance(v_inter, h_inter, mlx->player, ray_angle);
	draw_line(&(mlx->img), mlx->player.x, mlx->player.y, res.pos.x, res.pos.y, WHITE);
	int ca = fix_angle(mlx->player.angle - res.angle);
	res.distance = res.distance * cos_wrap(fix_angle(mlx->player.angle - res.angle));
	res.wall_height = (WINDOW_HEIGHT * 100) / res.distance;
	return (res);
}
