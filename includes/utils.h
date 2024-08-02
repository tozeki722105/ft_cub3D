
#ifndef UTILS_H
# define UTILS_H

#if defined(__linux__)
	#include "mlx.h"
#else
	#include "mlx.h" 
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
	// int	x;
	// int y;
	double	x;
	double	y;
} t_pos;


#endif