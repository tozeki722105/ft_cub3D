/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map_data_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:36:07 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 18:52:50 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#define WALL '1'
#define SPACE ' '

static bool	validate_vertical_wall_and_fill_space(char **map_data, size_t x,
		t_dir step, char fill_char)
{
	size_t	i;
	size_t	end;
	size_t	y;

	end = ft_count_rows(map_data);
	if (end == 0)
		return (false);
	i = 0;
	y = i;
	if (step == BACK)
		y = end - 1;
	while (i++ < end && (map_data[y][x] == SPACE
		|| map_data[y][x] == fill_char))
	{
		map_data[y][x] = fill_char;
		y += (int)step;
	}
	if (map_data[y][x] == WALL)
		return (true);
	return (false);
}

static bool	validate_horizontal_wall_and_fill_space(char **map_data, size_t y,
		t_dir step, char fill_char)
{
	size_t	i;
	size_t	end;
	size_t	x;

	end = ft_strlen(map_data[y]);
	if (end == 0)
		return (false);
	i = 0;
	x = i;
	if (step == BACK)
		x = end - 1;
	while (i++ < end && (map_data[y][x] == SPACE
		|| map_data[y][x] == fill_char))
	{
		map_data[y][x] = fill_char;
		x += (int)step;
	}
	if (map_data[y][x] == WALL)
		return (true);
	return (false);
}

bool	validate_surrounded_wall_and_fill_space(char **map_data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map_data[y])
	{
		if (!validate_horizontal_wall_and_fill_space(map_data, y, FRONT, '!')
			|| !validate_horizontal_wall_and_fill_space(map_data, y, BACK, '!'))
			return (false);
		y++;
	}
	y = 0;
	x = 0;
	while (map_data[y][x])
	{
		if (!validate_vertical_wall_and_fill_space(map_data, x, FRONT, '!')
			|| !validate_vertical_wall_and_fill_space(map_data, x, BACK, '!'))
			return (false);
		x++;
	}
	return (true);
}
