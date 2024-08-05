#include "ogv1.h"
#include "calc.h"
#include "parse.h"
#include "draw.h"

void render(t_mlx *mlx)
{   
	// draw_background(mlx, WHITE);
	draw_ceiling_floor(mlx, mlx->textures.ceiling, mlx->textures.floor);
	draw_wall(mlx, WINDOW_WIDTH/2);
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

void	initialize_render(t_mlx *mlx, t_loader loader)
{
	mlx->handle = mlx_init();
	mlx->window = mlx_new_window(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT, "cuv3d"); 
	mlx->img.handle = mlx_new_image(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img.buffer = mlx_get_data_addr(mlx->img.handle, &(mlx->img.bits_per_pixel), &(mlx->img.line_size), &(mlx->img.endian));
	mlx->player.pos = loader.player_pos;
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
	free_loader(loader);
	render(&mlx);
	mlx_hook(mlx.window, 02, 1L << 0, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}
