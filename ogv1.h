#ifndef OGV1_H
# define OGV1_H

#include "./minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define	NORTH_TEX_PATH	"img/collect.xpm"
#define	SOUTH_TEX_PATH	"img/exit.xpm"
#define	WEST_TEX_PATH	"img/tile.xpm"
#define	EAST_TEX_PATH	"img/wall.xpm"

#define WINDOW_WIDTH	1000
#define WINDOW_HEIGHT	500

#define MAP_X_COUNT 10
#define MAP_Y_COUNT 10
#define	MAP_PADDING	10

#define ANGLE_STEP	5
#define MOVE_STEP	5

#define RAY_LENGTH 1000

#define FOV	60

enum	e_color
{
	RED		=	0xFF0000,
	GREEN	=	0x00FF00,
	BLUE	=	0x0000FF,
	WHITE	=	0xFFFFFF,
	BLACK	=	0x000000,
	GRAY	=	0x505050,
	PURPLE	=	0x4F00FF,
	SKY		=	0x00C1FF,
	BROWN	=	0x764B00,
};

enum	e_key_code
{
	KEY_W		= 13,
	KEY_S		= 1,
	KEY_A		= 0,
	KEY_D		= 2,
	KEY_ESC		= 53,
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124
};

typedef enum e_direction
{
	NORTH	= 0,
	SOUTH	= 1,
	EAST	= 2,
	WEST	= 3,
}	t_direct;

enum	e_axis
{
	VERTICAL,
	HORIZONTAL,
};

typedef struct s_img
{
	void	*handle;
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_player
{
	double x;
	double y;
	double angle;
	double pdx; //視線のX成分
	double pdy; //視線のY成分
	int	side;
} t_player;

typedef struct s_map
{
	char **data;
	int	x_count; //mapX パネルのx方向の個数
	int y_count; //mapY パネルのy方向の個数
	int panel_side; //パネルの一辺s
} t_map;

typedef struct s_texture
{
	void	*handle;
	int		width;
	int		height;
} t_tex;

typedef struct s_intersection
{
	int			x;
	int			y;
	double		distance;
	double		wall_height;
	enum e_axis	touching_axis; //接している軸 vertical or horizontal
	int			origin_offset;
} t_intersection;

typedef struct s_mlx
{
	void		*handle;
	void		*window;
	t_img		img;
	t_tex		*textures;
	t_player	player;
	t_map		map;
}	t_mlx;

#endif