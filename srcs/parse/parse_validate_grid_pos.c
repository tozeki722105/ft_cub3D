/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:31:41 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/29 19:36:03 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	validate_grid_pos(char **map_data, t_pos *grid_pos)
{
	t_pos	cur;

	cur.y = 0;
	while (map_data[(int)cur.y])
	{
		cur.x = 0;
		while (map_data[(int)cur.y][(int)cur.x])
		{
			if (is_player(map_data[(int)cur.y][(int)cur.x]))
			{
				if (grid_pos->x == -1 && grid_pos->y == -1)
					*grid_pos = cur;
				else
					return (false);
			}
			cur.x++;
		}
		cur.y++;
	}
	if (grid_pos->x == -1 || grid_pos->y == -1)
		return (false);
	return (true);
}
