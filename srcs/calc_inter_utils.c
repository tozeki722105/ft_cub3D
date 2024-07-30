#include "calc.h"
#include "ogv1.h"
#include "config.h"

void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color)
{
	if (pos.x < (mlx->map.x_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2))
		&& pos.x > (rect_size / 2) + (rect_size % 2)
		&& pos.y > (rect_size / 2) + (rect_size % 2)
		&& pos.y < (mlx->map.y_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2)))
		draw_rect(&(mlx->img), pos.x - (rect_size / 2), pos.y - (rect_size / 2), rect_size, rect_size, color);
}

/// @brief fix distance from fisheye. and, calc wall_height.
double calc_wall_height(t_inter inter, t_player player)
{
	double fixed_distance;

	fixed_distance = inter.distance
		* cos_wrap(fix_angle(player.angle - inter.angle));
	return ((WINDOW_HEIGHT * 100) / fixed_distance); //map_panel_side??
}