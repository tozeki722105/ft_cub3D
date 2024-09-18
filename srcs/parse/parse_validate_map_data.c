/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:31:41 by tyamauch          #+#    #+#             */
/*   Updated: 2024/09/18 18:09:19 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	is_wall_or_space(char c)
{
	return (c == ' ' || c == '1');
}

static bool	is_surrounded_wall_or_space(char **map_data, size_t y, size_t x)
{
	return ((y == 0 || is_wall_or_space(map_data[y - 1][x]))
		&& (x == 0 || is_wall_or_space(map_data[y][x - 1]))
		&& (map_data[y][x + 1] == '\0' || is_wall_or_space(map_data[y][x + 1]))
		&& (map_data[y + 1] == NULL || is_wall_or_space(map_data[y + 1][x])));
}

static bool	validate_surrounded_wall(char **map_data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			if (map_data[y][x] == ' '
				&& !is_surrounded_wall_or_space(map_data, y, x))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map_data(char **map_data)
{
	char	**map_cpy;

	map_cpy = double_strdup_pad_space(map_data);
	if (!validate_surrounded_wall(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (false);
	}
	ft_free_double_str(map_cpy);
	return (true);
}
