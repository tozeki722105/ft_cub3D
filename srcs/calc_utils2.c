#include "calc.h"

double fix_angle(double angle)
{
	if (angle < 0.0)
		return (angle + 360.0);
	if (angle >= 360.0)
		return (angle - 360.0);
	return (angle);
}

t_pos	fix_move(t_mlx *mlx, t_pos pos, double move_angle, int step)
{
	t_inter inter;
	t_pos	res;

	inter = calc_intersection(mlx, move_angle);
	if (inter.distance < step + 20)
		step = 0;
	res.x = mlx->player.pos.x + (step * cos_wrap(move_angle));
	res.y = mlx->player.pos.y - (step * sin_wrap(move_angle));
	return (res);
}

bool	is_up(double degree)
{
	return (sin_wrap(degree) > 0.0001);	
}

bool	is_right(double degree)
{
	return (cos_wrap(degree) > 0.0001);
}
