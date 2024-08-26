/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:46:09 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 19:46:10 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "config.h"
# include "utils.h"

typedef struct s_image
{
	void		*handle;
	char		*buffer;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_player
{
	t_pos		pos;
	double		angle;
}				t_player;

typedef struct s_map
{
	char		**data;
	int			height;
	int			width;
	int			panel_side;
	int			x_count;
	int			y_count;
}				t_map;

typedef struct s_texture
{
	t_image		north;
	t_image		south;
	t_image		west;
	t_image		east;
	int			floor;
	int			ceiling;
}				t_tex;

typedef struct s_mlx
{
	void		*handle;
	void		*window;
	t_image		img;
	t_tex		textures;
	t_player	player;
	t_map		map;
}				t_mlx;

#endif
