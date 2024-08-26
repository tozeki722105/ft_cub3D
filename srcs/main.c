#include "main.h"
#include "calc.h"
#include "parse.h"
#include "draw.h"
#include "utils.h"

void render(t_mlx *mlx)
{   
	// draw_background(mlx, WHITE);
	draw_ceiling_floor(mlx, mlx->textures.ceiling, mlx->textures.floor);
	draw_wall(mlx);
	// draw_map(mlx, GRAY, BLACK);
	// draw_square_center_safely(mlx, mlx->player.pos, PLAYER_SIDE, WHITE);
	mlx_put_image_to_window(mlx->handle, mlx->window, mlx->img.handle, 0, 0);
}

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

int	destroy_window_hook(void)
{
	exit(0);
}

void	initialize_render(t_mlx *mlx, t_loader loader)
{
	mlx->handle = ft_x_mlx_init();
	mlx->window = ft_x_mlx_new_window(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d"); 
	mlx->img.handle = ft_x_mlx_new_image(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img.buffer = mlx_get_data_addr(mlx->img.handle, &(mlx->img.bits_per_pixel), &(mlx->img.line_size), &(mlx->img.endian));
	mlx->player.pos = loader.player_pos;
	mlx->player.angle = loader.player_angle;
	mlx->map.data = ft_x_double_str_dup(loader.map_data);
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
	mlx->textures.ceiling = loader.ceiling_color;
	mlx->textures.floor = loader.floor_color;
}

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q cub3d");
// }

#include "string.h"
int main(int argc, char* argv[])
{
	t_mlx mlx;
	t_loader loader;

	if (argc != 2)
		ft_my_perror_exit("Incorrect number of arguments", 1);
	loader = parse(argv[1]);
	initialize_render(&mlx, loader);
	free_loader(loader);	
	render(&mlx);
	mlx_hook(mlx.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, destroy_window_hook, &mlx);
	mlx_hook(mlx.window, KEYPRESS, KEYPRESS_MASK, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}

	
// mlx.handle = mlx_init();
// 	mlx.window = mlx_new_window(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d");
// 	mlx.player.pos.x = 251;
// 	mlx.player.pos.y = 251;
// 	mlx.player.angle = 63.7;//63.7
// 	mlx.img.handle = mlx_new_image(mlx.handle, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	mlx.img.buffer = mlx_get_data_addr(mlx.img.handle, &mlx.img.bits_per_pixel, &mlx.img.line_size, &mlx.img.endian);
// 	mlx.map.x_count = 10;
// 	mlx.map.y_count = 10;
// 	mlx.map.panel_side = WINDOW_HEIGHT / mlx.map.y_count;
// 	mlx.map.height = mlx.map.y_count * mlx.map.panel_side;
// 	mlx.map.width =  mlx.map.x_count * mlx.map.panel_side;
// 	mlx.map.data = (char **)malloc(sizeof(char *) * mlx.map.panel_side);
// 	mlx.map.data[0] = strdup("1111111111");
// 	mlx.map.data[1] = strdup("1010001001");
// 	mlx.map.data[2] = strdup("1010001001");
// 	mlx.map.data[3] = strdup("1010000001");
// 	mlx.map.data[4] = strdup("1000000001");
// 	mlx.map.data[5] = strdup("1000100001");
// 	mlx.map.data[6] = strdup("1000100001");
// 	mlx.map.data[7] = strdup("1000000001");
// 	mlx.map.data[8] = strdup("1000000101");
// 	mlx.map.data[9] = strdup("1111111111");
// 	//mlx.textures.north.handle = mlx_xpm_file_to_image(mlx.handle, "./img/collect.xpm", &(mlx.textures.north.width), &(mlx.textures.north.height));
// 	mlx.textures.north.handle = mlx_xpm_file_to_image(mlx.handle, "./img/mini-capy.xpm", &(mlx.textures.north.width), &(mlx.textures.north.height));
// 	mlx.textures.north.buffer = mlx_get_data_addr(mlx.textures.north.handle, &(mlx.textures.north.bits_per_pixel), &(mlx.textures.north.line_size), &(mlx.textures.north.endian));
// 	mlx.textures.south.handle = mlx_xpm_file_to_image(mlx.handle, "./img/exit.xpm", &(mlx.textures.south.width), &(mlx.textures.south.height));
// 	mlx.textures.south.buffer = mlx_get_data_addr(mlx.textures.south.handle, &(mlx.textures.south.bits_per_pixel), &(mlx.textures.south.line_size), &(mlx.textures.south.endian));
// 	mlx.textures.west.handle = mlx_xpm_file_to_image(mlx.handle, "./img/tile.xpm", &(mlx.textures.west.width), &(mlx.textures.west.height));
// 	mlx.textures.west.buffer = mlx_get_data_addr(mlx.textures.west.handle, &(mlx.textures.west.bits_per_pixel), &(mlx.textures.west.line_size), &(mlx.textures.west.endian));
// 	mlx.textures.east.handle = mlx_xpm_file_to_image(mlx.handle, "./img/wall.xpm", &(mlx.textures.east.width), &(mlx.textures.east.height));
// 	mlx.textures.east.buffer = mlx_get_data_addr(mlx.textures.east.handle, &(mlx.textures.east.bits_per_pixel), &(mlx.textures.east.line_size), &(mlx.textures.east.endian));
