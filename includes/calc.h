#ifndef CALC_H
# define CALC_H

#include "utils.h"
#include <math.h>

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

double calc_distance(double ray_angle, t_player player, t_intersection res);
double calc_offset(double ray_angle, enum e_axis axis, t_intersection inter, t_map map, t_mlx *mlx);
int get_vartical_first(t_mlx *mlx, int *pos_y, double ray_angle);
int		get_horizontal_first(t_mlx *mlx, int *pos_y, double ray_angle);
void	display_vartical_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
void	display_horizontal_grid_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection display_vertical_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection display_horizontal_intersection(t_mlx *mlx, t_intersection pos, int color, double ray_angle);
t_intersection	find_vartical_intersection(t_mlx *mlx, double ray_angle);
t_intersection	find_horizontal_intersection(t_mlx *mlx, double ray_angle);
t_intersection calc_intersection(t_mlx *mlx, double ray_angle);

void calc_test(t_mlx *mlx, double ray_angle);

#endif