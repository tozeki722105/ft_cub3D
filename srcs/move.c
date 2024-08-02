#include "ogv1.h"
#include "calc.h"


t_pos	fix_move(t_mlx *mlx, t_pos pos, double move_angle, int step)
{
	t_inter inter;
	t_pos cur;
	t_pos res;

	cur.x = mlx->player.pos.x;
	cur.y = mlx->player.pos.y;
	inter = new_calc_inter(mlx, move_angle);
	// printf("angle=%lf, distanec=%lf\n", move_angle, inter.distance);
	// if (inter.distance < step + 20)
	// {
	// 	step = 0;
	// }
	res.x = cur.x + (step * cos_wrap(move_angle));
	res.y = cur.y - (step * sin_wrap(move_angle));
	return (res);
}
	// double f_ang = fix_angle(move_angle);

	// if (inter.distance < step)
	// {
	// 	step = inter.distance;
	// }
	// res.x = pos.x + (step * cos_wrap(f_ang));
	// res.y = pos.y - (step * sin_wrap(f_ang));