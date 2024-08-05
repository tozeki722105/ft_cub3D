#include "../main.h"

//0・1~89
int get_vartical_first_1(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x = (((int)player.pos.x / map.panel_side) * map.panel_side) + map.panel_side;
	*pos_y = player.pos.y - ((pos_x - player.pos.x) * tan_wrap(ray_angle));
	return (pos_x);
}

//91~179
int get_vartical_first_2(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x = (((int)player.pos.x / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	*pos_y = player.pos.y - ((player.pos.x - pos_x) * -tan_wrap(ray_angle));
	return (pos_x);
}

//180・181~269
int get_vartical_first_3(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x = (((int)player.pos.x / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	*pos_y = player.pos.y + ((player.pos.x - pos_x) * tan_wrap(ray_angle));
	return (pos_x);
}

//271~359
int get_vartical_first_4(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x = (((int)player.pos.x / map.panel_side) * map.panel_side) + map.panel_side;
	*pos_y = player.pos.y + ((pos_x - player.pos.x) * -tan_wrap(ray_angle));
	return (pos_x);
}

void	display_vartical_grid_intersection(t_mlx *mlx, t_intersection pos, int color)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	if (is_right(player))
	{
		while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			printf("[%d][%d] ", pos.y / map.panel_side, pos.x / map.panel_side);
			pos.x += map.panel_side;
			pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(player.angle));
		}
		printf("\n");
	}
	else
	{
		while (pos.x > 0 && pos.x < end && pos.y > 0 && pos.y < WINDOW_HEIGHT)
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			printf("[%d][%d] ", pos.y / map.panel_side, pos.x / map.panel_side);
			pos.x -= map.panel_side;
			pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(player.angle));
		}
		printf("\n");
	}
}

void display_vertical_intersection(t_mlx *mlx, t_intersection pos, int color)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	// printf("map[%d][%d]\n", pos.y / map.panel_side, pos.x / map.panel_side);
	if (is_right(player))
	{
		while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
		{
			if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1') //なぜこれで座標が取れる?
			{
				draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
				return ;
			}
			pos.x += map.panel_side;
			pos.y = player.pos.y - ((pos.x - player.pos.x) * tan_wrap(player.angle));
		}
	}
	else
	{
		while (pos.x > 0 && pos.x < end && pos.y > 0 && pos.y < WINDOW_HEIGHT)
		{
			if (map.data[(pos.y / map.panel_side)][(pos.x / map.panel_side)] == '1')
			{
				draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
				return ;
			}
			pos.x -= map.panel_side;
			pos.y = player.pos.y + ((pos.x - player.pos.x) * -tan_wrap(player.angle));
		}
	}
}




t_pos display_horizontal_intersection(t_mlx *mlx, t_intersection pos, int color)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.y_count * map.panel_side;
	t_pos ret;
	if (is_up(player))
	{
		while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
		{
			if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
			{
				draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
				ret.x = pos.x;
				ret.y = pos.y;
				return (ret);
			}
			pos.y -= map.panel_side;
			pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(player.angle));
		}
	}
	else
	{
		while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
		{
			if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
			{
				draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
				ret.x = pos.x;
				ret.y = pos.y;
				return (ret);
			}
			pos.y += map.panel_side;
			pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(player.angle));
		}
	}
	ret.x = -1;
	ret.y = -1;
	return (ret);
}

void display_horizontal_grid_intersection(t_mlx *mlx, t_intersection pos, int color)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.y_count * map.panel_side;
	if (is_up(player))
	{
		while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
		{
			draw_rect(&(mlx->img), pos.x-5, pos.y-5, 10, 10, color);
			pos.y -= map.panel_side;
			pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(player.angle));
		}
	}
	else
	{
		while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
		{
			draw_rect(&(mlx->img), pos.x-5, pos.y-5, 10, 10, color);
			pos.y += map.panel_side;
			pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(player.angle));
		}
	}
}

int		get_horizontal_first(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int pos_x = 0;
	if (ray_angle > 0 && ray_angle <= 90)
	{
		*pos_y = (((int)player.pos.y / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
		pos_x = player.pos.x + ((player.pos.y - *pos_y) * cot_wrap(ray_angle));
	}
	else if (ray_angle > 90 && ray_angle < 180)
	{
		*pos_y = (((int)player.pos.y / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
		pos_x = player.pos.x - ((player.pos.y - *pos_y) * -cot_wrap(ray_angle));
	}
	else if (ray_angle > 180 && ray_angle <= 270)
	{
		*pos_y = (((int)player.pos.y / map.panel_side) * map.panel_side) + map.panel_side;
		pos_x = player.pos.x - ((*pos_y - player.pos.y) * cot_wrap(ray_angle));
	}
	else if (ray_angle > 270 && ray_angle <= 359)
	{
		*pos_y = (((int)player.pos.y / map.panel_side) * map.panel_side) + map.panel_side;
		pos_x = player.pos.x + ((*pos_y - player.pos.y) * -cot_wrap(ray_angle));
	}
	// draw_rect(&(mlx->img), pos_x-5, *pos_y-5, 10, 10, SKY);
	return (pos_x);
}

t_pos	find_horizontal_intersection(t_mlx *mlx)
{
	t_player player;
	t_intersection first;
	
	player = mlx->player;
	if ((int)player.angle == 0 || (int)player.angle == 180)
		return ((t_pos){-1,-1});
	first.x = get_horizontal_first(mlx, &(first.y), player.angle);
	// display_horizontal_grid_intersection(mlx, first, GREEN);
	return (display_horizontal_intersection(mlx, first, PURPLE));
	
	
}