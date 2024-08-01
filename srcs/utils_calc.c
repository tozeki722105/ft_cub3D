#include "ogv1.h"
#include "calc.h"

double fix_angle(double angle);
double convert_radian(double angle);
double cos_wrap(double angle);
double sin_wrap(double angle);
double tan_wrap(double angle);
double cot_wrap(double angle);
bool	is_up(double degree);
bool	is_right(double degree);
double calc_distance(double ray_angle, t_player player, t_intersection res);
//double calc_offset(double ray_angle, enum e_axis axis, t_intersection inter, t_map map, t_mlx *mlx);

void	display_ver_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color);
void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color);
void	display_horizontal_grid_inter(t_mlx *mlx, double ray_angle, t_pos pos, int color);
// double fix_pos(double pos_x, double pos_y, double *res_y)
// {
// 	int res_x;
// 	if (pos_x < MAP_PADDING)
// 		res_x = MAP_PADDING;
// 	else if (pos_x > WINDOW_WIDTH - MAP_PADDING)
// 		res_x = WINDOW_WIDTH - MAP_PADDING;
// 	else
// 		res_x = pos_x;
// 	if (pos_y < MAP_PADDING)
// 		*res_y = MAP_PADDING;
// 	else if (pos_y > WINDOW_HEIGHT - MAP_PADDING)
// 		*res_y = WINDOW_HEIGHT - MAP_PADDING;
// 	else
// 		*res_y = pos_y;
// 	return (res_x);
// }
//
double calc_distance(double ray_angle, t_player player, t_intersection res)
{
	return (cos_wrap(ray_angle) * (res.x - player.x) - sin_wrap(ray_angle) * (res.y - player.y));
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

void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color)
{
	if (pos.x < (mlx->map.x_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2))
		&& pos.x > (rect_size / 2) + (rect_size % 2)
		&& pos.y > (rect_size / 2) + (rect_size % 2)
		&& pos.y < (mlx->map.y_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2)))
		draw_rect(&(mlx->img), pos.x - (rect_size / 2), pos.y - (rect_size / 2), rect_size, rect_size, color);
}

double fix_angle(double angle)
{
	if (angle < 0.0)
		return (angle + 360.0);
	if (angle >= 360.0)
		return (angle - 360.0);
	return (angle);
}

double convert_radian(double angle)
{
	return ((angle * M_PI) / 180);
}

double cos_wrap(double angle)
{
	return (cos(convert_radian(angle)));
}

//0から180はプラス、181から359はマイナス
double sin_wrap(double angle)
{
	return (sin(convert_radian(angle)));
}

//91から179 & 271から359 はマイナス
double tan_wrap(double angle)
{
	return (tan(convert_radian(angle)));
}

//91から179 & 271から359 はマイナス
double cot_wrap(double angle)
{
	return (1.0 / tan_wrap(angle));
}

bool	is_up(double degree)
{
	return (sin_wrap(degree) > 0.0001);	
}

bool	is_right(double degree)
{
	return (cos_wrap(degree) > 0.0001);
}

// //mapように調節
// int fix_pos_x(int pos_x)
// {
// 	if (pos_x < 0)
// 		return (0);
// 	if (pos_x > WINDOW_WIDTH / 2)
// 		return (WINDOW_WIDTH / 2);
// 	return (pos_x);
// }

// int fix_pos_y(int pos_y)
// {
// 	if (pos_y < 0)
// 		return (0);
// 	if (pos_y > WINDOW_HEIGHT)
// 		return (WINDOW_HEIGHT);
// 	return (pos_y);
// }
