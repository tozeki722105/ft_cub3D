#include "calc.h"
#include "ogv1.h"

t_inter new_calc_inter(t_mlx *mlx, double ray_angle)
{
	t_pos *v_inter_pos;
	t_pos *h_inter_pos;
	t_inter	inter;

	v_inter_pos = search_vertical_inter(mlx, ray_angle);
	h_inter_pos = search_horizontal_inter(mlx, ray_angle);
	inter = compare_make_inter(mlx, v_inter_pos, h_inter_pos, ray_angle);
	if (v_inter_pos)
		free(v_inter_pos);
	if (h_inter_pos)
		free(h_inter_pos);
	return (inter);
}
