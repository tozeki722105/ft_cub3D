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