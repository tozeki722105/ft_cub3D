/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_calc_horizontal_inter_pos.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 04:52:43 by toshi             #+#    #+#             */
/*   Updated: 2024/08/26 14:30:34 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "draw.h"

static t_pos	calc_horizontal_start_pos(t_mlx *mlx, double ray_angle)
{
	t_player	player;
	t_map		map;
	t_pos		pos;
	int			panel_origin_y;

	player = mlx->player;
	map = mlx->map;
	panel_origin_y = ((int)player.pos.y / map.panel_side) * map.panel_side;
	if (player.pos.y == panel_origin_y || is_up(ray_angle))
		pos.y = panel_origin_y;
	else
		pos.y = panel_origin_y + map.panel_side;
	pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	return (pos);
}

static t_pos	search_horizontal_inter_pos(t_mlx *mlx, double ray_angle,
		t_pos pos)
{
	t_map		map;
	t_player	player;
	t_point		point;
	int			step;
	int			flag;

	map = mlx->map;
	player = mlx->player;
	flag = is_up(ray_angle);
	step = map.panel_side;
	if (is_up(ray_angle))
		step *= -1;
	while (pos.x < map.width && pos.x > 0 && pos.y > 0 && pos.y < map.height)
	{
		point.y = ((int)pos.y / map.panel_side) - flag;
		point.x = (int)pos.x / map.panel_side;
		if (map.data[point.y][point.x] == '1')
			return (pos);
		pos.y += step;
		pos.x = player.pos.x + ((player.pos.y - pos.y) * cot_wrap(ray_angle));
	}
	return ((t_pos){-1, -1});
}

t_pos	*calc_horizontal_inter_pos(t_mlx *mlx, double ray_angle)
{
	t_pos	*pos;

	if ((int)ray_angle == 0 || (int)ray_angle == 180)
		return (NULL);
	pos = (t_pos *)ft_x_malloc(sizeof(t_pos));
	*pos = calc_horizontal_start_pos(mlx, ray_angle);
	*pos = search_horizontal_inter_pos(mlx, ray_angle, *pos);
	if (pos->x == -1 || pos->y == -1)
	{
		free(pos);
		return (NULL);
	}
	return (pos);
}
