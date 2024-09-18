/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:06:46 by tyamauch          #+#    #+#             */
/*   Updated: 2024/09/18 18:07:04 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_pos			*calc_vertical_inter_pos(t_mlx *mlx, double ray_angle);
t_pos			*calc_horizontal_inter_pos(t_mlx *mlx, double ray_angle);

static double	calc_distance(t_pos *pos, t_player player, double ray_angle)
{
	if (!pos)
		return (-1);
	return (cos_wrap(ray_angle) * (pos->x - player.pos.x) - sin_wrap(ray_angle)
		* (pos->y - player.pos.y));
}

static double	calc_origin_offset(t_inter inter, int map_panel_side)
{
	if (inter.axis == HORIZONTAL)
	{
		if (is_up(inter.angle))
			return (inter.pos.x - (((int)inter.pos.x / map_panel_side)
					* map_panel_side));
		else
			return (((((int)inter.pos.x / map_panel_side) * map_panel_side)
					+ map_panel_side) - inter.pos.x);
	}
	else
	{
		if (is_right(inter.angle))
			return (inter.pos.y - (((int)inter.pos.y / map_panel_side)
					* map_panel_side));
		else
			return (((((int)inter.pos.y / map_panel_side) * map_panel_side)
					+ map_panel_side) - inter.pos.y);
	}
}

/// @brief fix distance from fisheye. and, calc wall_height.
double	calc_wall_height(t_inter inter, t_player player)
{
	double	fixed_distance;

	fixed_distance = inter.distance * cos_wrap(fix_angle(player.angle
				- inter.angle));
	return ((WINDOW_HEIGHT * WALL_HEIGHT_SCALE) / fixed_distance);
}

static t_inter	compare_make_intersection(t_mlx *mlx, t_pos *v_inter_pos,
		t_pos *h_inter_pos, double ray_angle)
{
	t_inter	inter;
	double	v_distance;
	double	h_distance;

	v_distance = calc_distance(v_inter_pos, mlx->player, ray_angle);
	h_distance = calc_distance(h_inter_pos, mlx->player, ray_angle);
	if (!h_inter_pos || (v_inter_pos && h_inter_pos && v_distance < h_distance))
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
	inter.origin_offset = calc_origin_offset(inter, mlx->map.panel_side);
	inter.wall_height = calc_wall_height(inter, mlx->player);
	return (inter);
}

t_inter	calc_intersection(t_mlx *mlx, double ray_angle)
{
	t_pos	*v_inter_pos;
	t_pos	*h_inter_pos;
	t_inter	inter;

	v_inter_pos = calc_vertical_inter_pos(mlx, ray_angle);
	h_inter_pos = calc_horizontal_inter_pos(mlx, ray_angle);
	if (!v_inter_pos && !h_inter_pos)
	{
		v_inter_pos = calc_vertical_inter_pos(mlx, ray_angle - 0.1);
		h_inter_pos = calc_horizontal_inter_pos(mlx, ray_angle - 0.1);
	}
	inter = compare_make_intersection(mlx, v_inter_pos, h_inter_pos, ray_angle);
	if (v_inter_pos)
		free(v_inter_pos);
	if (h_inter_pos)
		free(h_inter_pos);
	return (inter);
}
