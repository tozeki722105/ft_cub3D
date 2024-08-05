#ifndef OGV1_H
# define OGV1_H

#include "utils.h"
#include "config.h"

typedef struct s_img
{
	void	*handle;
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	t_pos	pos;
	double angle;
} t_player;

typedef struct s_map
{
	char **data;
	int height;
	int width;
	int panel_side;
	int	x_count;
	int y_count;
} t_map;

typedef struct s_texture
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	int 	floor;
	int		ceiling;
} t_tex;

typedef struct s_mlx
{
	void		*handle;
	void		*window;
	t_img		img;
	t_tex		textures;
	t_player	player;
	t_map		map;
}	t_mlx;

#endif
