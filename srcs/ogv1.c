#include "ogv1.h"

void render(t_mlx *mlx)
{   
	draw_background(&(mlx->img), WHITE);
	draw_map(mlx);
	draw_player(mlx);
	
	draw_line(&(mlx->img), mlx->player.x, mlx->player.y, 
		(mlx->player.x + (20 * cos_wrap(mlx->player.angle))), 
		(mlx->player.y - (20 * sin_wrap(mlx->player.angle))), 
		WHITE);
	// draw_wall(mlx, WINDOW_WIDTH/2);
	mlx_put_image_to_window(mlx->handle, mlx->window, mlx->img.handle, 0, 0);
}

// t_pos fix_move(t_pos pos, double angle)
// {
// 	t_pos next;

// 	pos.x += MOVE_STEP * cos_wrap(fix_angle(angle));
// 	pos.y -= MOVE_STEP * sin_wrap(fix_angle(angle));
// 	return (next);
// }

int	handle_keypress(int key, t_mlx *mlx)
{
	double next_angle;
	t_pos res;

	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_A)
	{
		// mlx->player.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle + 90));
		// mlx->player.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle + 90));
		res.x = mlx->player.x;
		res.y = mlx->player.y;
		res = fix_move(mlx, res, fix_angle(mlx->player.angle + 90), MOVE_STEP);
		mlx->player.x = res.x;
		mlx->player.y = res.y;
	}
	else if (key == KEY_D)
	{
		// mlx->player.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle - 90));
		// mlx->player.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle - 90));
		res.x = mlx->player.x;
		res.y = mlx->player.y;
		res = fix_move(mlx, res, fix_angle(mlx->player.angle - 90), MOVE_STEP);
		mlx->player.x = res.x;
		mlx->player.y = res.y;
	}
	else if (key == KEY_W)
	{
		// mlx->player.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle));
		// mlx->player.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle));
		res.x = mlx->player.x;
		res.y = mlx->player.y;
		res = fix_move(mlx, res, fix_angle(mlx->player.angle), MOVE_STEP);
		mlx->player.x = res.x;
		mlx->player.y = res.y;
	}
	else if (key == KEY_S)
	{
		// mlx->player.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle - 180));
		// mlx->player.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle - 180));
		res.x = mlx->player.x;
		res.y = mlx->player.y;
		res = fix_move(mlx, res, fix_angle(mlx->player.angle - 180), MOVE_STEP);
		mlx->player.x = res.x;
		mlx->player.y = res.y;
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
	mlx.player.x = 308;
	mlx.player.y = 312;
	mlx.player.angle = 90;//63.7
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

