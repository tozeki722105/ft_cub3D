/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:16:28 by tozeki            #+#    #+#             */
/*   Updated: 2024/08/26 20:32:29 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "calc.h"
#include "parse.h"
#include "draw.h"
#include "utils.h"

// void	initialize_mlx(t_mlx *mlx, t_loader loader);

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q cub3d");
// }

void	render(t_mlx *mlx)
{
	draw_ceiling_floor(mlx, mlx->textures.ceiling, mlx->textures.floor);
	draw_wall(mlx);
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

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_loader	loader;

	if (argc != 2)
		ft_my_perror_exit("Incorrect number of arguments", 1);
	loader = parse(argv[1]);
	initialize_mlx(&mlx, loader);
	free_loader(loader);
	render(&mlx);
	mlx_hook(mlx.window, DESTROY_NOTIFY, 1L << 17, destroy_window_hook, &mlx);
	mlx_hook(mlx.window, KEYPRESS, 1L << 0, &handle_keypress, &mlx);
	mlx_loop(mlx.handle);
}
