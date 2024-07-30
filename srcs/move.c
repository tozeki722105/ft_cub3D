#include "ogv1.h"
#include "calc.h"

// t_intersection move_inter(t_mlx *mlx, double ray_angle)
// {
// 	t_player player;
// 	t_map map;

// 	player = mlx->player;
// 	map = mlx->map;
// 	t_intersection v_inter = find_vartical_intersection(mlx, ray_angle);
// 	t_intersection h_inter = find_horizontal_intersection(mlx, ray_angle);
// 	t_intersection res = compare_distance(v_inter, h_inter, player, ray_angle);
// 	res.distance = res.distance * cos_wrap(fix_angle(ray_angle - res.degree));
// 	return (res);
// }

t_pos	fix_move(t_mlx *mlx, t_pos pos, double move_angle, int step)
{
	t_intersection inter;
	t_pos cur;
	t_pos res;

	cur.x = mlx->player.x;
	cur.y = mlx->player.y;
	inter = move_inter(mlx, move_angle);
	printf("angle=%lf, distanec=%lf\n", move_angle, inter.distance);
	if (inter.distance < step + 20)
	{
		step = 0;
	}
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