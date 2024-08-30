/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:40:32 by tozeki            #+#    #+#             */
/*   Updated: 2024/08/26 19:53:25 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "calc.h"
#include "parse.h"
#include "draw.h"
#include "utils.h"

static void	initialize_img_textures(t_mlx *mlx, t_loader loader)
{
	mlx->textures.north.handle = ft_x_mlx_xpm_file_to_image(mlx->handle,
			loader.north_path, &(mlx->textures.north.width),
			&(mlx->textures.north.height));
	mlx->textures.north.buffer = ft_x_mlx_get_data_addr(mlx->textures.north.handle,
			&(mlx->textures.north.bits_per_pixel),
			&(mlx->textures.north.line_size), &(mlx->textures.north.endian));
	mlx->textures.south.handle = ft_x_mlx_xpm_file_to_image(mlx->handle,
			loader.south_path, &(mlx->textures.south.width),
			&(mlx->textures.south.height));
	mlx->textures.south.buffer = ft_x_mlx_get_data_addr(mlx->textures.south.handle,
			&(mlx->textures.south.bits_per_pixel),
			&(mlx->textures.south.line_size), &(mlx->textures.south.endian));
	mlx->textures.west.handle = ft_x_mlx_xpm_file_to_image(mlx->handle,
			loader.west_path, &(mlx->textures.west.width),
			&(mlx->textures.west.height));
	mlx->textures.west.buffer = ft_x_mlx_get_data_addr(mlx->textures.west.handle,
			&(mlx->textures.west.bits_per_pixel),
			&(mlx->textures.west.line_size), &(mlx->textures.west.endian));
	mlx->textures.east.handle = ft_x_mlx_xpm_file_to_image(mlx->handle,
			loader.east_path, &(mlx->textures.east.width),
			&(mlx->textures.east.height));
	mlx->textures.east.buffer = ft_x_mlx_get_data_addr(mlx->textures.east.handle,
			&(mlx->textures.east.bits_per_pixel),
			&(mlx->textures.east.line_size), &(mlx->textures.east.endian));
}

void	initialize_mlx(t_mlx *mlx, t_loader loader)
{
	mlx->handle = ft_x_mlx_init();
	mlx->window = ft_x_mlx_new_window(mlx->handle, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cuv3d");
	mlx->img.handle = ft_x_mlx_new_image(mlx->handle, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	mlx->img.buffer = ft_x_mlx_get_data_addr(mlx->img.handle,
			&(mlx->img.bits_per_pixel), &(mlx->img.line_size),
			&(mlx->img.endian));
	mlx->player.pos = loader.player_pos;
	mlx->player.angle = loader.player_angle;
	mlx->map.data = ft_x_double_str_dup(loader.map_data);
	mlx->map.y_count = loader.map_y_count;
	mlx->map.x_count = loader.map_x_count;
	mlx->map.panel_side = MAP_PANEL_SIDE;
	mlx->map.height = loader.map_y_count * mlx->map.panel_side;
	mlx->map.width = loader.map_x_count * mlx->map.panel_side;
	initialize_img_textures(mlx, loader);
	mlx->textures.ceiling = loader.ceiling_color;
	mlx->textures.floor = loader.floor_color;
}
