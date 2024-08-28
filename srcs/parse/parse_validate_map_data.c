/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:31:41 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/28 22:16:45 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool		validate_surrounded_wall_and_fill_space(char **map_data);

// static bool	is_filled_map_element(char c)
// {
// 	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
// 		|| c == '!');
// }

// static bool	validate_map_elements(char **map_data)
// {
// 	size_t	y;
// 	size_t	x;

// 	y = 0;
// 	while (map_data[y])
// 	{
// 		x = 0;
// 		while (map_data[y][x])
// 		{
// 			if (!is_map_element(map_data[y][x]))
// 				return (false);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

// static bool	validate_map_size(char **map_data)
// {
// 	size_t	y;

// 	y = 0;
// 	while (map_data[y])
// 		y++;
// 	if (y < 4)
// 		return (false);
// 	y = 0;
// 	while (map_data[y])
// 	{
// 		if (ft_strlen(map_data[y]) < 4)
// 			return (false);
// 		y++;
// 	}
// 	return (true);
// }

char *double_strdup_pad_space_helper(char *str, size_t x_count, bool padding_flag)
{
	char *res;

	res = (char *)ft_x_malloc((x_count + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memset(res, ' ', x_count);
	res[x_count] = '\0';
	if (!padding_flag)
		ft_memmove(res + sizeof(char), str, ft_strlen(str));
	return (res);
}

char	**double_strdup_pad_space(char **d_str)
{
	char	**res;
	size_t	i;
	size_t	y_count;
	size_t 	x_count;

	y_count = ft_count_rows(d_str) + 2;
	res = (char **)ft_x_malloc((y_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	x_count = ft_strlen(*d_str) + 2;
	i = 0;
	while (i < y_count)
	{
		res[i] = double_strdup_pad_space_helper(*d_str, 
			x_count, (i == 0 || i == y_count - 1));
		if (!res[i])
		{
			ft_free_double_str(res);
			return (NULL);
		}
		d_str += !(i == 0 || i == y_count - 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}

bool is_wall_or_space(char c)
{
	return (c == ' ' || c == '1');
}

bool is_surrounded_wall_or_space(char **map_data, size_t y, size_t x)
{
	return ((y == 0 || is_wall_or_space(map_data[y - 1][x]))
		&& (x == 0 || is_wall_or_space(map_data[y][x - 1]))
		&& (map_data[y][x + 1] == '\0' || is_wall_or_space(map_data[y][x + 1]))
		&& (map_data[y + 1]) == NULL || is_wall_or_space(map_data[y + 1][x]));
}

bool validate_surrounded_wall(char **map_data)
{
	size_t y;
	size_t x;
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

	print_map_data(map_data);
	map_cpy = double_strdup_pad_space(map_data);
	print_map_data(map_cpy);
	if (!validate_surrounded_wall(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (ft_my_perror_ret_false("The map is not surrounded by walls"));
	}
	ft_free_double_str(map_cpy);
	return (true);
	// if (!validate_map_size(map_data))
	// 	return (ft_my_perror_ret_false("The map size is too small"));
	// map_cpy = ft_x_double_str_dup(map_data);
	// if (!validate_surrounded_wall_and_fill_space(map_cpy))
	// {
	// 	ft_free_double_str(map_cpy);
	// 	return (ft_my_perror_ret_false("The map is not surrounded by walls"));
	// }
	// print_map_data(map_data);
	// if (!validate_map_elements(map_data))
	// {
	// 	// ft_free_double_str(map_cpy);
	// 	return (ft_my_perror_ret_false("There is space in the map area"));
	// }
	// print_map_data(map_cpy);
	// exit(1);
}
