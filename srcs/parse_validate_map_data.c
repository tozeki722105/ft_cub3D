#include "parse.h"

bool	validate_surrounded_wall_and_fill_space(char **map_data);

static bool	is_filled_map_element(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '!');
}

static bool	validate_map_elements(char **map_data)
{
	size_t y;
	size_t x;

	y = 0;
	while (map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			if (!is_filled_map_element(map_data[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	validate_map_size(char **map_data)
{
	size_t y;

	y = 0;
	while (map_data[y])
		y++;
	if (y < 4)
		return (false);
	y = 0;
	while (map_data[y])
	{
		if (ft_strlen(map_data[y]) < 4)
			return (false);
		y++;
	}
	return (true);
}

bool	validate_map_data(char **map_data)
{
	char **map_cpy;

	if (!validate_map_size(map_data))
		return (ft_my_perror_ret_false("The map size is too small"));
	map_cpy = ft_x_double_str_dup(map_data);
	if (!validate_surrounded_wall_and_fill_space(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (ft_my_perror_ret_false("The map is not surrounded by walls"));
	}
	if (!validate_map_elements(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (ft_my_perror_ret_false("There is space in the map area"));
	}
	ft_free_double_str(map_cpy);
	return (true);
}
