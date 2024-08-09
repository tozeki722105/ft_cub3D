#include "draw.h"

void	draw_square(t_mlx *mlx, t_pos origin_pos, int side, int color)
{
	int	y;
	int x;

	y = 0;
	while (y < side)
	{
		x = 0;
		while (x < side)
			put_pixel(&(mlx->img), (int)origin_pos.x + x++, (int)origin_pos.y + y, 
				color);
		y++;
	}
}

void	draw_square_center(t_mlx *mlx, t_pos center_pos, int side, int color)
{
	int	y;
	int x;

	y = 0;
	while (y < side)
	{
		x = 0;
		while (x < side)
			put_pixel(&(mlx->img), (int)center_pos.x - ((side / 2) + (side % 2)) + x++,
				(int)center_pos.y - ((side / 2) + (side % 2)) + y, color);
		y++;
	}
}

void draw_square_safely(t_mlx *mlx, t_pos origin_pos, size_t size, int color)
{
	if (origin_pos.x >= 0
		&& origin_pos.x < mlx->map.width - size
		&& origin_pos.y >= 0
		&& origin_pos.y < mlx->map.height - size)
		draw_square(mlx, origin_pos, size, color);
}

void draw_square_center_safely(t_mlx *mlx, t_pos center_pos, size_t size, int color)
{
	int half_size;

	half_size = (size / 2) + (size % 2);
	if (center_pos.x >= half_size
		&& center_pos.x < mlx->map.width - half_size
		&& center_pos.y >= half_size
		&& center_pos.y < mlx->map.height - half_size)
		draw_square_center(mlx, center_pos, size, color);
}

// void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color)
// {
// 	if (pos.x < (mlx->map.x_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2))
// 		&& pos.x > (rect_size / 2) + (rect_size % 2)
// 		&& pos.y > (rect_size / 2) + (rect_size % 2)
// 		&& pos.y < (mlx->map.y_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2)))
// 		draw_rect(&(mlx->img), pos.x - (rect_size / 2), pos.y - (rect_size / 2), rect_size, rect_size, color);
// }
