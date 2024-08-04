#include "ogv1.h"
#include "config.h"

void	put_pixel(t_img *img, int x, int y, int color);
int		pick_color(t_img *img, int x, int y);
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void	draw_background(t_img *img, int color);
void	draw_rect(t_img *img, int x, int y, int width, int height, int color);
void	draw_map(t_mlx *mlx);
void	draw_player(t_mlx *mlx);

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

void	draw_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			put_pixel(img, j++, i, color);
		i++;
	}
}

void	draw_rect(t_img *img, int x, int y, int width, int height, int color)
{
	int	i;
	int j;

	i = y;
	while (i < y + height)
	{
		j = x;
		while (j < x + width)
			put_pixel(img, j++, i, color);
		i++;
	}
}

void draw_map(t_mlx *mlx)
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
			if (map.data[y][x] == '1')
				color = BLACK;
			else
				color = GRAY;
			draw_rect(&(mlx->img), (x * map.panel_side) + 1, (y * map.panel_side) + 1, 
				map.panel_side - 2, map.panel_side - 2, color);
			x++;
		}
		y++;
	}
}

void draw_player(t_mlx *mlx)
{
	t_player player;
	int half_side;

	player = mlx->player;
	half_side = PLAYER_SIDE / 2;
	draw_rect(&(mlx->img), player.pos.x - half_side, player.pos.y - half_side, PLAYER_SIDE, PLAYER_SIDE, WHITE);	
}

void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color)
{
	if (pos.x < (mlx->map.x_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2))
		&& pos.x > (rect_size / 2) + (rect_size % 2)
		&& pos.y > (rect_size / 2) + (rect_size % 2)
		&& pos.y < (mlx->map.y_count * mlx->map.panel_side) - (rect_size + (rect_size / 2) + (rect_size % 2)))
		draw_rect(&(mlx->img), pos.x - (rect_size / 2), pos.y - (rect_size / 2), rect_size, rect_size, color);
}
