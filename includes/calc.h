#ifndef CALC_H
# define CALC_H

#include "utils.h"
#include <math.h>
#include "ogv1.h"

#define	BOUND_ADJUSTMENT	0.001

enum	e_axis
{
	VERTICAL,
	HORIZONTAL,
};

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

typedef struct s_inter
{
	t_pos		pos;
	double		distance;
	enum e_axis	axis; //接している軸 vertical or horizontal
	double		angle;
	int			origin_offset; //or orign_x & origin_y
	double		wall_height;
} t_inter;

// calc_inter.c
t_inter new_calc_inter(t_mlx *mlx, double ray_angle);

// calc_inter_utils.c
void draw_rect_safely(t_mlx *mlx, t_pos pos, size_t rect_size, int color);
double calc_wall_height(t_inter inter, t_player player);

// calc_compare_make_inter.c
t_inter	compare_make_inter(t_mlx *mlx, t_pos *v_inter_pos, t_pos *h_inter_pos, double ray_angle);

// calc_search_horizontal_inter.c
t_pos *search_horizontal_inter(t_mlx *mlx, double ray_angle);

// calc_search_vertical_inter.c
t_pos *search_vertical_inter(t_mlx *mlx, double ray_angle);

#endif
