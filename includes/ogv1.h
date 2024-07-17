#ifndef OGV1_H
# define OGV1_H

#if (__linux)
	#include "mlx.h"
#else
	#include "./minilibx_opengl_20191021/mlx.h" 
#endif
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#define BUFFER_SIZE 42

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

#define SYSERR	-1

#define	BOUND_ADJUSTMENT	0.001


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

/* linux用 */
#if (__linux)
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

typedef	enum e_parse_kind
{
	KIND_MAP,
	WALL,
	KIND_NORTH,
	KIND_SOUTH,
	KIND_WEST,
	KIND_EAST,
	FLOOR_CEILING,
	KIND_FLOOR,
	KIND_CEILING,
	KIND_NEWLINE,
	KIND_FALSE,
}	t_parse_kind;

// typedef enum e_direction
// {
// 	NORTH	= 0,
// 	SOUTH	= 1,
// 	EAST	= 2,
// 	WEST	= 3,
// }	t_direct;

enum	e_axis
{
	VERTICAL,
	HORIZONTAL,
};

typedef struct s_pos
{
	int	x;
	int y;
} t_pos;

typedef struct s_map_node
{
	char *val;
	struct s_map_node *next;
}	t_mnode;

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

typedef struct s_texture
{
	t_src	north;
	t_src	south;
	t_src	west;
	t_src	east;
	int 	floor;
	int		ceiling;
} t_tex;


typedef struct s_intersection
{
	enum e_axis	touching_axis; //接している軸 vertical or horizontal
	int			x;
	int			y;
	double		distance;
	double		wall_height;
	int			origin_offset;
	double		degree;
} t_intersection;

typedef struct s_mlx
{
	void		*handle;
	void		*window;
	t_img		img;
	t_tex		textures;
	t_player	player;
	t_map		map;
}	t_mlx;

void	put_pixel(t_img *img, int x, int y, int color);
int		pick_color(t_src *img, int x, int y);
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void	draw_background(t_img *img, int color);
void	draw_rect(t_img *img, int x, int y, int width, int height, int color);
void	draw_map(t_mlx *mlx);
void	draw_player(t_mlx *mlx);

double fix_angle(double angle);
double convert_radian(double angle);
double cos_wrap(double angle);
double sin_wrap(double angle);
double tan_wrap(double angle);
double cot_wrap(double angle);
bool	is_up(double degree);
bool	is_right(double degree);


int		get_vartical_first(t_mlx *mlx, int *pos_y, int ray_angle);
int		get_horizontal_first(t_mlx *mlx, int *pos_y, double ray_angle);
void	display_vartical_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
void	display_horizontal_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection display_vertical_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection display_horizontal_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection	find_vartical_intersection(t_mlx *mlx, double ray_angle);
t_intersection	find_horizontal_intersection(t_mlx *mlx, double ray_angle);
t_intersection calc_intersection(t_mlx *mlx, double ray_angle);

void draw_wall(t_mlx *mlx, int start);

#endif
