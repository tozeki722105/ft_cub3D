#include "draw.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
    *((int *)pixel) = color;
}

int		pick_color(t_img *img, int x, int y)
{
	char    *pixel;

    pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
    return(*((int *)pixel));
}

//chatgpt
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        put_pixel(img, x1, y1, color); // 現在のピクセルを描画
        if (x1 == x2 && y1 == y2) break; // 終点に到達したらループを終了
        e2 = 2 * err; // エラー項を2倍
        if (e2 > -dy) // 水平方向のエラーが許容範囲内
        {
            err -= dy;
            x1 += sx; // 次のピクセルのx座標を更新
        }
        if (e2 < dx) // 垂直方向のエラーが許容範囲内
        {
            err += dx;
            y1 += sy; // 次のピクセルのy座標を更新
        }
    }
}

void draw_map(t_mlx *mlx, int floor_color, int wall_color)
{
	t_map map;
	size_t y;
	size_t x;
	int color;

	map = mlx->map;
	y = 0;
	while (y < map.y_count)
	{
		x = 0;
		while (x < map.x_count)
		{
			color = floor_color;
			if (map.data[y][x] == '1')
				color = wall_color;
			draw_square_safely(mlx, (t_pos){(x * map.panel_side) + 1,
				(y * map.panel_side) + 1}, map.panel_side - 2, color);
			x++;
		}
		y++;
	}
}
