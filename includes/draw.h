/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:45:45 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 19:45:47 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "main.h"

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

// draw_wall.c
void	draw_wall(t_mlx *mlx);

//draw_utils.c
void	put_pixel(t_image *img, int x, int y, int color);
int		pick_color(t_image *img, int x, int y);
void	draw_line(t_image *img, t_point player, t_point inter, int color);
void	draw_map(t_mlx *mlx, int floor_color, int wall_color);

//draw_background.c
void	draw_ceiling_floor(t_mlx *mlx, int ceiling_color, int floor_color);
void	draw_background(t_mlx *mlx, int color);

//draw_rect.c
void	draw_square(t_mlx *mlx, t_pos origin_pos, int side, int color);
void	draw_square_center(t_mlx *mlx, t_pos center_pos, int side, int color);
void	draw_square_safely(t_mlx *mlx, t_pos origin_pos, size_t size,
			int color);
void	draw_square_center_safely(t_mlx *mlx, t_pos center_pos, size_t size,
			int color);
#endif
