#ifndef CALC_H
# define CALC_H

#include <math.h>
#include "main.h"
#include "draw.h"
#include "../library/libft/libft.h"

enum	e_axis
{
	VERTICAL,
	HORIZONTAL,
};

typedef struct s_inter
{
	t_pos		pos;
	double		distance;
	enum e_axis	axis;
	double		angle;
	int			origin_offset;
	double		wall_height;
} t_inter;

//calc_interseciton.c
t_inter calc_intersection(t_mlx *mlx, double ray_angle);

//calc_utils.c
double sin_wrap(double angle);
double cos_wrap(double angle);
double tan_wrap(double angle);
double cot_wrap(double angle);

//calc_utils2.c
double fix_angle(double angle);
t_pos	fix_move(t_mlx *mlx, t_pos pos, double move_angle, int step);
bool	is_up(double degree);
bool	is_right(double degree);

#endif
