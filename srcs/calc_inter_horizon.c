#include "ogv1.h"
#include "calc.h"

static t_pos calc_horizontal_start(t_mlx *mlx, double ray_angle)
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

static t_pos calc_horizontal_inter(t_mlx *mlx, double ray_angle, t_pos *f_pos)
{
	t_map map;
	/* t_player player; */
	double scalar;
	t_pos pos;

	map = mlx->map;
	/* player = mlx->player; */
	scalar = fabs((double)(map.panel_side)/f_pos->y) ;
	pos.x = mlx->player.x + f_pos->x;
	pos.y = mlx->player.y + f_pos->y;
	int diff =0;
	if (is_up(ray_angle))
		diff = -1;
	while (pos.x < map.width && pos.x > 0 
		&& pos.y > 0 && pos.y < map.height)
	{
		if (map.data[pos.y / map.panel_side + diff ][pos.x / map.panel_side ] == '1')
			return (pos);
		pos.y += f_pos->y * scalar;
		pos.x += f_pos->x * scalar;
	}
	printf("no pos\n");
	if(pos.x < 0)
		pos.x = 0;
	if(pos.y < 0)
		pos.y = 0;
	return (pos);
}

/* static t_pos *find_calc_h_inter(t_mlx *mlx, double ray_angle) */
t_pos *find_calc_h_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *pos;
	t_pos f_pos;

	/* if ((int)ray_angle == 0 || (int)ray_angle == 180) */
	/* 	return (NULL); */
	f_pos = calc_horizontal_start(mlx, ray_angle);//pos(274,200)
	if(f_pos.x == 0 || f_pos.y == 0)
	{
		printf("no pos\n");
		return(NULL);
	}
	pos = (t_pos *)malloc(sizeof(t_pos));
	// display_horizontal_grid_inter(mlx, ray_angle, *pos, GREEN);
	*pos = calc_horizontal_inter(mlx, ray_angle, &f_pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free (pos);
		return (NULL);
	}
	return (pos);
}
