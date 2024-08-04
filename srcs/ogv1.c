#include "ogv1.h"
#include "calc.h"
#include "config.h"
#include "parse.h"

void render(t_mlx *mlx)
{   
	draw_background(&(mlx->img), WHITE);
	draw_wall(mlx, WINDOW_WIDTH/2);
	mlx_put_image_to_window(mlx->handle, mlx->window, mlx->img.handle, 0, 0);
}
	// draw_map(mlx);
	// draw_player(mlx);
	// search_vertical_inter(mlx, mlx->player.angle);

int	handle_keypress(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_A)
		mlx->player.pos = fix_move(mlx, mlx->player.pos, 
			fix_angle(mlx->player.angle + 90.0), MOVE_STEP);
	else if (key == KEY_D)
		mlx->player.pos = fix_move(mlx, mlx->player.pos, 
			fix_angle(mlx->player.angle - 90.0), MOVE_STEP);
	else if (key == KEY_W)
		mlx->player.pos = fix_move(mlx, mlx->player.pos, 
			mlx->player.angle, MOVE_STEP);
	else if (key == KEY_S)
		mlx->player.pos = fix_move(mlx, mlx->player.pos, 
			fix_angle(mlx->player.angle - 180.0), MOVE_STEP);
	else if (key == KEY_LEFT)
		mlx->player.angle = fix_angle(mlx->player.angle + ANGLE_STEP);
	else if (key == KEY_RIGHT)
		mlx->player.angle = fix_angle(mlx->player.angle - ANGLE_STEP);
	else
		return (1);
	render(mlx);
	return (0);
}
	// double next_angle;
	// t_pos res;
		// mlx->player.pos.x -= MOVE_STEP;
		// mlx->player.pos.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle + 90));
		// mlx->player.pos.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle + 90));
		// res.x = mlx->player.pos.x;
		// res.y = mlx->player.pos.y;
		// res = fix_move(mlx, res, fix_angle(mlx->player.angle + 90.0), MOVE_STEP);
		// mlx->player.pos.x = res.x;
		// mlx->player.pos.y = res.y;
		// mlx->player.pos.x += MOVE_STEP;
		// mlx->player.pos.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle - 90));
		// mlx->player.pos.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle - 90));
		// res.x = mlx->player.pos.x;
		// res.y = mlx->player.pos.y;
		// res = fix_move(mlx, res, fix_angle(mlx->player.angle - 90.0), MOVE_STEP);
		// mlx->player.pos.x = res.x;
		// mlx->player.pos.y = res.y;
		// mlx->player.pos.y -= MOVE_STEP;
		// mlx->player.pos.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle));
		// mlx->player.pos.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle));
		// res.x = mlx->player.pos.x;
		// res.y = mlx->player.pos.y;
		// res = fix_move(mlx, res, mlx->player.angle, MOVE_STEP);
		// mlx->player.pos.x = res.x;
		// mlx->player.pos.y = res.y;
		// mlx->player.pos.y += MOVE_STEP;
		// mlx->player.pos.x += MOVE_STEP * cos_wrap(fix_angle(mlx->player.angle - 180));
		// mlx->player.pos.y -= MOVE_STEP * sin_wrap(fix_angle(mlx->player.angle - 180));
		// res.x = mlx->player.pos.x;
		// res.y = mlx->player.pos.y;
		// res = fix_move(mlx, res, fix_angle(mlx->player.angle - 180.0), MOVE_STEP);
		// mlx->player.pos.x = res.x;
		// mlx->player.pos.y = res.y;

t_pos	convert_player_pos(t_loader loader)
{
	t_pos	pos;

	pos.x = (loader.player_pos.x * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	pos.y = (loader.player_pos.y * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	// pos.x = 70;
	// pos.y = 70;
	return (pos);
}

void	initialize_render(t_mlx *mlx, t_loader loader)
{
	mlx->handle = mlx_init();
	mlx->window = mlx_new_window(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d"); 
	mlx->img.handle = mlx_new_image(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img.buffer = mlx_get_data_addr(mlx->img.handle, &(mlx->img.bits_per_pixel), &(mlx->img.line_size), &(mlx->img.endian));
	mlx->player.pos = convert_player_pos(loader);
	mlx->player.angle = loader.player_angle;
	mlx->map.data = ft_double_str_dup(loader.map_data);
	mlx->map.y_count = loader.map_y_count;
	mlx->map.x_count = loader.map_x_count;
	mlx->map.panel_side = MAP_PANEL_SIDE;
	mlx->map.height = loader.map_y_count * mlx->map.panel_side;
	mlx->map.width = loader.map_x_count * mlx->map.panel_side;
	mlx->textures.north.handle = mlx_xpm_file_to_image(mlx->handle, loader.north_path, &(mlx->textures.north.width), &(mlx->textures.north.height));
	mlx->textures.north.buffer = mlx_get_data_addr(mlx->textures.north.handle, &(mlx->textures.north.bits_per_pixel), &(mlx->textures.north.line_size), &(mlx->textures.north.endian));
	mlx->textures.south.handle = mlx_xpm_file_to_image(mlx->handle, loader.south_path, &(mlx->textures.south.width), &(mlx->textures.south.height));
	mlx->textures.south.buffer = mlx_get_data_addr(mlx->textures.south.handle, &(mlx->textures.south.bits_per_pixel), &(mlx->textures.south.line_size), &(mlx->textures.south.endian));
	mlx->textures.west.handle = mlx_xpm_file_to_image(mlx->handle, loader.west_path, &(mlx->textures.west.width), &(mlx->textures.west.height));
	mlx->textures.west.buffer = mlx_get_data_addr(mlx->textures.west.handle, &(mlx->textures.west.bits_per_pixel), &(mlx->textures.west.line_size), &(mlx->textures.west.endian));
	mlx->textures.east.handle = mlx_xpm_file_to_image(mlx->handle, loader.east_path, &(mlx->textures.east.width), &(mlx->textures.east.height));
	mlx->textures.east.buffer = mlx_get_data_addr(mlx->textures.east.handle, &(mlx->textures.east.bits_per_pixel), &(mlx->textures.east.line_size), &(mlx->textures.east.endian));
}

int main(int argc, char* argv[])
{
	t_mlx mlx;
	t_loader loader;	

	if (argc != 2)
		return (1);
	loader = parse(argv[1]);
	initialize_render(&mlx, loader);
	// printf("p.x=%lf, p.y=%lf, p.angle=%lf\n", mlx.player.pos.x, mlx.player.pos.y, mlx.player.angle);
	//render
	render(&mlx);
	//loop
	mlx_hook(mlx.window, 02, 1L << 0, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}
	// mlx->player.side = 10;
// void	print_mlx(t_mlx mlx)
// {
// 	prin
// }

// #include "string.h"


	// mlx.handle = mlx_init(); //定数
	// mlx.window = mlx_new_window(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d"); 
	// mlx.player.pos.x = 251; //convert
	// mlx.player.pos.y = 251;
	// mlx.player.angle = 63.7;//63.7
	// mlx.player.side = 10; //定数
	// mlx.img.handle = mlx_new_image(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT); //定数
	// mlx.img.buffer = mlx_get_data_addr(mlx.img.handle, &mlx.img.bits_per_pixel, &mlx.img.line_size, &mlx.img.endian);
	// mlx.map.x_count = MAP_X_COUNT;//loader.map.count <- まだ受け取ってない
	// mlx.map.y_count = MAP_Y_COUNT; 
	// mlx.map.panel_side = WINDOW_HEIGHT / MAP_Y_COUNT; //定数
	// mlx.map.height = mlx.map.y_count * mlx.map.panel_side; //loader.map.count * 定数
	// mlx.map.width =  mlx.map.x_count * mlx.map.panel_side; 
	// mlx.map.data = (char **)malloc(sizeof(char *) * MAP_Y_COUNT); //loaderから直接
	// mlx.map.data[0] = strdup("1111111111");
	// mlx.map.data[1] = strdup("1010001001");
	// mlx.map.data[2] = strdup("1010001001");
	// mlx.map.data[3] = strdup("1010000001");
	// mlx.map.data[4] = strdup("1000000001");
	// mlx.map.data[5] = strdup("1000100001");
	// mlx.map.data[6] = strdup("1000100001");
	// mlx.map.data[7] = strdup("1000000001");
	// mlx.map.data[8] = strdup("1000000101");
	// mlx.map.data[9] = strdup("1111111111");
	// mlx.textures.north.handle = mlx_xpm_file_to_image(mlx.handle, NORTH_TEX_PATH, &(mlx.textures.north.width), &(mlx.textures.north.height));
	// mlx.textures.north.buffer = mlx_get_data_addr(mlx.textures.north.handle, &(mlx.textures.north.bits_per_pixel), &(mlx.textures.north.line_size), &(mlx.textures.north.endian));
	// mlx.textures.south.handle = mlx_xpm_file_to_image(mlx.handle, SOUTH_TEX_PATH, &(mlx.textures.south.width), &(mlx.textures.south.height));
	// mlx.textures.south.buffer = mlx_get_data_addr(mlx.textures.south.handle, &(mlx.textures.south.bits_per_pixel), &(mlx.textures.south.line_size), &(mlx.textures.south.endian));
	// mlx.textures.west.handle = mlx_xpm_file_to_image(mlx.handle, WEST_TEX_PATH, &(mlx.textures.west.width), &(mlx.textures.west.height));
	// mlx.textures.west.buffer = mlx_get_data_addr(mlx.textures.west.handle, &(mlx.textures.west.bits_per_pixel), &(mlx.textures.west.line_size), &(mlx.textures.west.endian));
	// mlx.textures.east.handle = mlx_xpm_file_to_image(mlx.handle, EAST_TEX_PATH, &(mlx.textures.east.width), &(mlx.textures.east.height));
	// mlx.textures.east.buffer = mlx_get_data_addr(mlx.textures.east.handle, &(mlx.textures.east.bits_per_pixel), &(mlx.textures.east.line_size), &(mlx.textures.east.endian));