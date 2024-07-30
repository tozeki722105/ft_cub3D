#include "calc.h"
#include "ogv1.h"

static double	calc_distance(t_pos *pos, t_player player, double ray_angle)
{
	if (!pos)
		return (-1);
	return (cos_wrap(ray_angle) * (pos->x - player.x)
		- sin_wrap(ray_angle) * (pos->y - player.y));
}

static int	calc_origin_offset(t_inter inter, int map_panel_side)
{
	if (inter.axis == HORIZONTAL)
	{
		if (is_up(inter.angle))
			return (inter.pos.x - ((inter.pos.x / map_panel_side) * map_panel_side));
		else
			return ((((inter.pos.x / map_panel_side) * map_panel_side) + map_panel_side) - inter.pos.x);
	}
	else
	{
		if (is_right(inter.angle))
			return (inter.pos.y - ((inter.pos.y / map_panel_side) * map_panel_side));
		else
			return ((((inter.pos.y / map_panel_side) * map_panel_side) + map_panel_side) - inter.pos.y);
	}
}

/// @brief use calc_img_x 
static int	calc_origin(t_inter inter, int map_panel_side)
{
	if (inter.axis == HORIZONTAL)
	{
		if (is_up(inter.angle))
			return (((int)inter.pos.x / map_panel_side) * map_panel_side);
		else
			return (((int)inter.pos.x / map_panel_side) * map_panel_side) + map_panel_side;
	}
	else
	{
		if (is_right(inter.angle))
			return (((int)inter.pos.y / map_panel_side) * map_panel_side);
		else
			return (((int)inter.pos.y / map_panel_side) * map_panel_side) + map_panel_side;
	}
}

t_inter	compare_make_inter(t_mlx *mlx, t_pos *v_inter_pos, t_pos *h_inter_pos, double ray_angle)
{
	t_inter inter;
	double	v_distance;
	double	h_distance;

	v_distance = calc_distance(v_inter_pos, mlx->player, ray_angle);
	h_distance = calc_distance(h_inter_pos, mlx->player, ray_angle);
	if (h_distance == -1
		|| (v_inter_pos && h_inter_pos && v_distance < h_distance))
	{
		inter.axis = VERTICAL;
		inter.pos = *v_inter_pos;
		inter.distance = v_distance;
	}
	else
	{
		inter.axis = HORIZONTAL;
		inter.pos = *h_inter_pos;
		inter.distance = h_distance;
	}
	inter.angle = ray_angle;
	inter.origin_offset = calc_origin(inter, mlx->map.panel_side);
	inter.wall_height = calc_wall_height(inter, mlx->player);
	return (inter);
}