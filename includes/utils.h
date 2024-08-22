#ifndef UTILS_H
# define UTILS_H

#if defined(__linux__)
	#include "../library/minilibx-linux/mlx.h"
	#include "mlx_int.h"
#else
	#include "../library/minilibx_opengl_20191021/mlx.h"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

#define SYSERR	-1

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

typedef struct s_pos
{
	double	x;
	double	y;
} t_pos;

void	*ft_x_mlx_init();
#if defined(__linux__)
	void	*ft_x_mlx_new_image(t_xvar *xvar,int width, int height);
	void	*ft_x_mlx_new_window(t_xvar *xvar,int size_x,int size_y,char *title);
#else
	void	*ft_x_mlx_new_image(void *mlx_ptr,int width,int height);
	void	*ft_x_mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
#endif

#endif
