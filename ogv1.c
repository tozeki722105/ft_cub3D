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

bool	is_right(t_player player)
{
	return (cos_wrap(player.angle) > 0.0001);	
}

bool	is_up(t_player player)
{
	return (sin_wrap(player.angle) > 0.0001);	
}

bool	is_up2(double degree)
{
	return (sin_wrap(degree) > 0.0001);	
}

bool	is_right2(double degree)
{
	return (cos_wrap(degree) > 0.0001);
}

double culc_offset(double ray_angle, enum e_axis axis, t_intersection inter, t_map map, t_mlx *mlx)
{
	double res;
	if (axis == HORIZONTAL)
	{
		if (is_up2(ray_angle))
		{
			res = (((int)inter.x / map.panel_side) * map.panel_side);
			// draw_rect(&(mlx->img), res-5, inter.y-5, 10, 10, RED);
		}
		else
		{
			res = (((int)inter.x / map.panel_side) * map.panel_side) + map.panel_side;
			// draw_rect(&(mlx->img), res-5, inter.y-5, 10, 10, RED);
		}
	}
	else
	{
		if (is_right2(ray_angle))
		{
			res = (((int)inter.y / map.panel_side) * map.panel_side);
			// draw_rect(&(mlx->img), inter.x-5, res-5, 10, 10, RED);
		}
		else
		{
			res = (((int)inter.y / map.panel_side) * map.panel_side) + map.panel_side;
			// draw_rect(&(mlx->img), inter.x-5, res-5, 10, 10, RED);
		}
	}
	return (res);
}

int get_vartical_first(t_mlx *mlx, int *pos_y, int ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	size_t i =0;
	int pos_x;
	if (is_right(player))
		pos_x = (((int)player.x / map.panel_side) * map.panel_side) + map.panel_side;
	else
		pos_x = (((int)player.x / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	*pos_y = player.y - ((pos_x - player.x) * tan_wrap(ray_angle));
	// draw_rect(&(mlx->img), pos_x-5, *pos_y-5, 10, 10, SKY);
	return (pos_x);
}

void	display_vartical_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	int add = map.panel_side;
	if (!is_right(player))
		add *= -1;
	while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
	{
		draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
		// printf("[%d][%d] ", pos.y / map.panel_side, pos.x / map.panel_side);
		pos.x += add;
		pos.y = player.y - ((pos.x - player.x) * tan_wrap(ray_angle));
	}
	// printf("\n");
}

double calc_distance(double ray_angle, t_player player, t_intersection res)
{
	return (cos_wrap(ray_angle) * (res.x - player.x) - sin_wrap(ray_angle) * (res.y - player.y));	
}

t_intersection display_vertical_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.x_count * map.panel_side;
	int add = map.panel_side;
	t_intersection res;
	if (!is_right2(ray_angle))
		add *= -1;
	while (pos.x < end && pos.x > 0 && pos.y > 0 && pos.y < WINDOW_HEIGHT)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			res.touching_axis = VERTICAL;
			res.x = pos.x;
			res.y = pos.y;
			res.degree = ray_angle;
			res.distance = calc_distance(ray_angle, player, res);
			res.origin_offset = culc_offset(ray_angle, res.touching_axis, pos, map, mlx);
			return (res);
		}
		pos.x += add;
		pos.y = player.y + ((player.x - pos.x) * tan_wrap(ray_angle));
	}
	return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
}
t_intersection display_horizontal_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	t_intersection res;
	int end = map.y_count * map.panel_side;
	int add = map.panel_side;
	if (is_up2(ray_angle))
		add *= -1;
	while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
	{
		if (map.data[pos.y / map.panel_side][pos.x / map.panel_side] == '1')
		{
			draw_rect(&(mlx->img), pos.x - 5, pos.y - 5, 10, 10, color);
			res.touching_axis = HORIZONTAL;
			res.x = pos.x;
			res.y = pos.y;
			res.degree = ray_angle;
			res.distance = calc_distance(ray_angle, player, res);
			res.origin_offset = culc_offset(ray_angle, res.touching_axis, pos, map, mlx);
			return (res);
		}
		pos.y += add;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
	return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
}

t_intersection	find_vartical_intersection(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_intersection first;
	
	player = mlx->player;
	if ((int)ray_angle == 90 || (int)ray_angle == 270)
		return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
	first.x = get_vartical_first(mlx, &(first.y), ray_angle);
	// display_vartical_grid_intersection(mlx, first, GREEN, ray_angle);
	return (display_vertical_intersection(mlx, first, BLUE, ray_angle));
}


void display_horizontal_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int end = map.y_count * map.panel_side;
	int add = map.panel_side;
	if (is_up2(ray_angle))
		add *= -1;
	while (pos.y > 0 && pos.y < end && pos.x > 0 && pos.x < WINDOW_WIDTH / 2)
	{
		draw_rect(&(mlx->img), pos.x-5, pos.y-5, 10, 10, color);
		pos.y += add;
		pos.x = player.x + ((player.y - pos.y) * cot_wrap(ray_angle));
	}
}

int		get_horizontal_first(t_mlx *mlx, int *pos_y, double ray_angle)
{
	t_map map = mlx->map;
	t_player player = mlx->player;
	int pos_x = 0;
	if (is_up2(ray_angle))
		*pos_y = (((int)player.y / map.panel_side) * map.panel_side) - BOUND_ADJUSTMENT;
	else
		*pos_y = (((int)player.y / map.panel_side) * map.panel_side) + map.panel_side;
	pos_x = player.x + ((player.y - *pos_y) * cot_wrap(ray_angle));
	return (pos_x);
}

t_intersection	find_horizontal_intersection(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_intersection first;
	
	player = mlx->player;
	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return ((t_intersection){0, 50000, 50000, 50000, 5000, 5000});
	first.x = get_horizontal_first(mlx, &(first.y), ray_angle);
	// display_horizontal_grid_intersection(mlx, first, GREEN, ray_angle);
	return (display_horizontal_intersection(mlx, first, RED, ray_angle));
}

//mapように調節
int fix_pos_x(int pos_x)
{
	if (pos_x < 0)
		return (0);
	if (pos_x > WINDOW_WIDTH / 2)
		return (WINDOW_WIDTH / 2);
	return (pos_x);
}

int fix_pos_y(int pos_y)
{
	if (pos_y < 0)
		return (0);
	if (pos_y > WINDOW_HEIGHT)
		return (WINDOW_HEIGHT);
	return (pos_y);
}

t_intersection compare_distance(t_intersection v_inter, t_intersection h_inter, t_player player, double ray_angle)
{
	// printf("vertical=%d; horizon=%d;\n", (int)v_inter.distance, (int)h_inter.distance);
	if (v_inter.x == 50000)
	{
		// printf("kkkk\n");
		return (h_inter);
	}
	if (h_inter.x == 50000)
	{
		// printf("bbbb");
		return (v_inter);
	}
	// int v_dist = cos_wrap(ray_angle) * (v_inter.x - player.x) - cos_wrap(ray_angle) * (v_inter.y - player.y);
	// int h_dist = cos_wrap(ray_angle) * (h_inter.x - player.x) - cos_wrap(ray_angle) * (h_inter.y - player.y);
	if (v_inter.distance < h_inter.distance)
		return (v_inter);
	else
		return (h_inter);
}

t_intersection draw_ray(t_mlx *mlx, double ray_angle)
{
	t_player player;
	t_map map;

	player = mlx->player;
	map = mlx->map;
	// printf("x=%d, y=%d\n", (int)(player.x + (cos_wrap(player.angle) * RAY_LENGTH)), (int)(player.y + (-1 * sin_wrap(player.angle) * RAY_LENGTH)));
	// int fx = (int)(player.x + (cos_wrap(player.angle) * RAY_LENGTH));
	// int fy = (int)(player.y + (-1 * sin_wrap(player.angle) * RAY_LENGTH));
	// draw_line(&(mlx->img), player.x, player.y, fx, fy, WHITE);
	t_intersection v_inter = find_vartical_intersection(mlx, ray_angle);
	t_intersection h_inter = find_horizontal_intersection(mlx, ray_angle);
	t_intersection res = compare_distance(v_inter, h_inter, player, ray_angle);
	draw_line(&(mlx->img), player.x, player.y, res.x, res.y, WHITE);
	int ca = fix_angle(player.angle - res.degree);
	res.distance = res.distance * cos_wrap(fix_angle(player.angle - res.degree));
	res.wall_height = (WINDOW_HEIGHT * 100) / res.distance;
	return (res);
}


int	pick_src(int src_x, t_src src, t_intersection inter, int y)
{
	int len = (src.height * y) / inter.wall_height;
	// return (src.buffer[len][src_x]);
	return (pick_color(&src, src_x, len));
}

t_src get_img(t_mlx *mlx, t_intersection intersection)
{
	
	if (intersection.touching_axis == HORIZONTAL)
	{
		if (is_up2(intersection.degree))
			return (mlx->textures.north);
		else
			return (mlx->textures.south);
	}
	else
	{
		if (is_right2(intersection.degree))
			return (mlx->textures.east);
		else
			return (mlx->textures.west);
	}
}

int calc_src_x(t_intersection inter, int x, t_mlx *mlx, t_src src)
{
	if (inter.touching_axis == HORIZONTAL)
	{
		if (is_up2(inter.degree))
			return (src.width * (int)abs(inter.origin_offset - inter.x) / mlx->map.panel_side);
		else
			return (src.width * (int)abs(inter.origin_offset - inter.x) / mlx->map.panel_side);
	}
	else
	{
		if (is_right2(inter.degree))
			return (src.height * (int)abs(inter.origin_offset - inter.y) / mlx->map.panel_side);
		else
			return (src.height * (int)abs(inter.origin_offset - inter.y) / mlx->map.panel_side);
	}
}

void draw_vertical_line_of_object(t_intersection intersection, int x, t_mlx *mlx)
{
	int y;
	int i;
	t_src src = get_img(mlx, intersection);

	y = (WINDOW_HEIGHT / 2) - ((int)intersection.wall_height / 2);
	int src_x = calc_src_x(intersection, x, mlx, src);
	i = 0;
	while (i < (int)intersection.wall_height)
	{
		put_pixel(&(mlx->img), x, y, pick_src(src_x, src, intersection, i));
		y++;
		i++;
	}
}

void draw_wall(t_mlx *mlx, int start)
{
	t_player player = mlx->player;
	t_map map = mlx->map;
	t_img img = mlx->img;
	double draw_angle_step;
	double draw_start_angle;
	int i;

	draw_start_angle = fix_angle(player.angle + (FOV / 2));
	draw_angle_step = (double)FOV / ((double)WINDOW_WIDTH / 2);
	i = start;
	while (i < WINDOW_WIDTH)
	{
		t_intersection res = draw_ray(mlx, draw_start_angle);
		draw_vertical_line_of_object(res, i, mlx);
		draw_start_angle = fix_angle(draw_start_angle - draw_angle_step);
		i++;
	}
}

void render(t_mlx *mlx)
{   
	draw_background(&(mlx->img), WHITE);
	draw_map(mlx);
	draw_player(mlx);
	// t_intersection res = draw_ray(mlx, mlx->player.angle);
	// draw_ray(mlx, mlx->player.angle);
	draw_wall(mlx, WINDOW_WIDTH/2);
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
	// printf("degree=%lf;\n", mlx->player.angle);
	render(mlx);
	return (0);
}

#include "string.h"
int main(int argc, char* argv[])
{
	t_mlx mlx;

	mlx.handle = mlx_init();
	mlx.window = mlx_new_window(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d");
	mlx.player.x = 250;
	mlx.player.y = 250;
	mlx.player.angle = 63.7;
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
	mlx.textures.north.handle = mlx_xpm_file_to_image(mlx.handle, NORTH_TEX_PATH, &(mlx.textures.north.width), &(mlx.textures.north.height));
	mlx.textures.north.buffer = mlx_get_data_addr(mlx.textures.north.handle, &(mlx.textures.north.bits_per_pixel), &(mlx.textures.north.line_size), &(mlx.textures.north.endian));
	mlx.textures.south.handle = mlx_xpm_file_to_image(mlx.handle, SOUTH_TEX_PATH, &(mlx.textures.south.width), &(mlx.textures.south.height));
	mlx.textures.south.buffer = mlx_get_data_addr(mlx.textures.south.handle, &(mlx.textures.south.bits_per_pixel), &(mlx.textures.south.line_size), &(mlx.textures.south.endian));
	mlx.textures.west.handle = mlx_xpm_file_to_image(mlx.handle, WEST_TEX_PATH, &(mlx.textures.west.width), &(mlx.textures.west.height));
	mlx.textures.west.buffer = mlx_get_data_addr(mlx.textures.west.handle, &(mlx.textures.west.bits_per_pixel), &(mlx.textures.west.line_size), &(mlx.textures.west.endian));
	mlx.textures.east.handle = mlx_xpm_file_to_image(mlx.handle, EAST_TEX_PATH, &(mlx.textures.east.width), &(mlx.textures.east.height));
	mlx.textures.east.buffer = mlx_get_data_addr(mlx.textures.east.handle, &(mlx.textures.east.bits_per_pixel), &(mlx.textures.east.line_size), &(mlx.textures.east.endian));

	//render
	render(&mlx);
	//loop
	mlx_hook(mlx.window, 02, 1L << 0, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}

