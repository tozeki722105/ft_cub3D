#include "ogv1.h"
#include "config.h"

void	put_pixel(t_img *img, int x, int y, int color);
int		pick_color(t_src *img, int x, int y);
/* void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color); */
void	draw_line(t_img *img, t_point player, t_point inter, int color);
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

int		pick_color(t_src *img, int x, int y)
{
	char    *pixel;

    pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
    return(*((int *)pixel));
}


static void set_value_draw_line(t_point *player,t_point *div,t_point *inter,t_point *direction,int *err)
{
				div->x =  abs(player->x - inter->x);
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
//chatgpt
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
        if (player.x == inter.x && player.y == inter.y) break; // 終点に到達したらループを終了
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
	half_side = player.side / 2;
	draw_rect(&(mlx->img), player.x - half_side, player.y - half_side, player.side, player.side, WHITE);	
}
