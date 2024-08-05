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

static void set_value_draw_line(t_point *player, t_point *div, 
	t_point *inter, t_point *direction, int *err)
{
	div->x = abs(player->x - inter->x);
	div->y = abs(player->y - inter->y);
	if(player->x < inter->x)
		direction->x = 1;
	else
		direction->x = -1;
	if(player->y < inter->y)
		direction->y = 1;
	else
		direction->y = -1;
	*err = div->x - div->y;
}

void	draw_line(t_img *img, t_point player, t_point inter, int color)
{
	t_point div;
	t_point direction;
	int err ;
	int e2 ;

	set_value_draw_line(&player,&div,&inter,&direction,&err);
    while (1)
    {
        put_pixel(img, player.x, player.y, color); // 現在のピクセルを描画
        if (player.x == inter.x && player.y == inter.y)
			break; // 終点に到達したらループを終了
        e2 = 2 * err; // エラー項を2倍
        if (e2 > -div.y) // 水平方向のエラーが許容範囲内
        {
            err -= div.y;
            player.x += direction.x; // 次のピクセルのx座標を更新
        }
        if (e2 < div.x) // 垂直方向のエラーが許容範囲内
        {
            err += div.x;
            player.y += direction.y; // 次のピクセルのy座標を更新
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
