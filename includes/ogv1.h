#ifndef OGV1_H
# define OGV1_H

#include "utils.h"
#include "config.h"

#define	NORTH_TEX_PATH	"img/collect.xpm"
#define	SOUTH_TEX_PATH	"img/exit.xpm"
#define	WEST_TEX_PATH	"img/tile.xpm"
#define	EAST_TEX_PATH	"img/wall.xpm"
#define MAP_X_COUNT 10
#define MAP_Y_COUNT 10

/* linux用 */
#if defined(__linux__)
enum	e_key_code
{
	KEY_W		= 119,
	KEY_S		= 115,
	KEY_A		= 97,
	KEY_D		= 100,
	/* KEY_ESC		= 27, */
	KEY_ESC		= 65307,
	KEY_LEFT	= 65361,
	KEY_RIGHT	= 65363
};
#else
/* mac用 */
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
#endif

typedef struct s_img
{
	int		width;
	int		height;
	void	*handle;
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_source
{
	int width;
	int height;
	void *handle;
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
} t_src;

typedef struct s_player
{
	// double x;
	// double y;
	t_pos	pos;
	double angle;
	// double pdx; //視線のX成分
	// double pdy; //視線のY成分
	// int	side;
} t_player;

typedef struct s_map
{
	char **data;
	int	x_count; //mapX パネルのx方向の個数
	int y_count; //mapY パネルのy方向の個数
	int panel_side; //パネルの一辺s
	int height;
	int width;
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
