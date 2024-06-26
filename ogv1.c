#include "ogv1.h"

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

double fix_angle(double angle)
{
	if (angle < 0)
		return (angle + 360);
	if (angle >= 360)
		return (angle - 360);
	return (angle);
}

double convert_radian(int angle)
{
	return ((angle * M_PI) / 180);
}

double cos_wrap(int angle)
{
	return (cos(convert_radian(angle)));
}

//sinは0~180は正、181~359は負の値のため、符号と進行方向が逆
double sin_wrap(int angle)
{
	return (sin(convert_radian(angle)));
}

double tan_wrap(int angle)
{
	return (tan(convert_radian(angle)));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->buffer + (y * img->line_size + x * (img->bits_per_pixel / 8));
    *((int *)pixel) = color;
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
	half_side = player.side / 2;
	draw_rect(&(mlx->img), player.x - half_side, player.y - half_side, player.side, player.side, WHITE);
	
}

void draw_ray(t_mlx *mlx)
{
	t_player player;

	player = mlx->player;
	printf("x=%d, y=%d\n", (int)(player.x + (cos_wrap(player.angle) * RAY_LENGTH)), (int)(player.y + (-1 * sin_wrap(player.angle) * RAY_LENGTH)));
	draw_line(&(mlx->img), player.x, player.y, (int)(player.x + (cos_wrap(player.angle) * RAY_LENGTH)), (int)(player.y + (-1 * sin_wrap(player.angle) * RAY_LENGTH)), WHITE);
}

void render(t_mlx *mlx)
{   
	draw_background(&(mlx->img), WHITE);
	draw_map(mlx);
	draw_player(mlx);
	draw_ray(mlx);
	mlx_put_image_to_window(mlx->handle, mlx->window, mlx->img.handle, 0, 0);
}

int	handle_keypress(int key, t_mlx *mlx)
{
	double next_angle;

	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_A)
	{
		if (mlx->player.x >= MOVE_STEP)
			mlx->player.x -= MOVE_STEP;
	}
	else if (key == KEY_D)
	{
		if (mlx->player.x + MOVE_STEP <= WINDOW_WIDTH)
			mlx->player.x += MOVE_STEP;
	}
	else if (key == KEY_W)
	{
		if (mlx->player.y >= MOVE_STEP)
			mlx->player.y -= MOVE_STEP;
	}
	else if (key == KEY_S)
	{
		if (mlx->player.y + MOVE_STEP <= WINDOW_HEIGHT)
			mlx->player.y += MOVE_STEP;
	}
	else if (key == KEY_LEFT)
		mlx->player.angle = fix_angle(mlx->player.angle + ANGLE_STEP);
	else if (key == KEY_RIGHT)
		mlx->player.angle = fix_angle(mlx->player.angle - ANGLE_STEP);
	else
		return (1);
	render(mlx);
	return (0);
}

#include "string.h"
int main(int argc, char* argv[])
{
	t_mlx mlx;

	mlx.handle = mlx_init();
	mlx.window = mlx_new_window(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d");
	mlx.player.x = 150;
	mlx.player.y = 400;
	mlx.player.angle = 90;
	mlx.player.pdx = cos_wrap(mlx.player.angle);
	mlx.player.pdy = -sin_wrap(mlx.player.angle);
	mlx.player.side = 10;
	mlx.img.handle = mlx_new_image(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx.img.buffer = mlx_get_data_addr(mlx.img.handle, &mlx.img.bits_per_pixel, &mlx.img.line_size, &mlx.img.endian);
	mlx.map.x_count = MAP_X_COUNT;
	mlx.map.y_count = MAP_Y_COUNT;
	mlx.map.panel_side = WINDOW_HEIGHT / MAP_Y_COUNT;
	mlx.map.data = (char **)malloc(sizeof(char *) * MAP_Y_COUNT);
	mlx.map.data[0] = strdup("1111111111");
	mlx.map.data[1] = strdup("1010001001");
	mlx.map.data[2] = strdup("1010001001");
	mlx.map.data[3] = strdup("1010000001");
	mlx.map.data[4] = strdup("1000000001");
	mlx.map.data[5] = strdup("1000100001");
	mlx.map.data[6] = strdup("1000100001");
	mlx.map.data[7] = strdup("1000000001");
	mlx.map.data[8] = strdup("1000000101");
	mlx.map.data[9] = strdup("1111111111");

	//render
	render(&mlx);
	//loop
	mlx_hook(mlx.window, 02, 1L << 0, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}

