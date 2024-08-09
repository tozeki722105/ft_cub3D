#include "parse.h"
#define WALL	'1'
#define SPACE	' '

static bool	validate_vertical_wall_and_fill_space(char **map_data, size_t x, int step, char fill_char)
{
	size_t i;
	size_t end;
	size_t y;

	end = ft_count_rows(map_data);
	if (end == 0)
		return (false);
	i = 0;
	y = i;
	if (step < 0)
		y = end - 1;
	while (i++ < end
		&& (map_data[y][x] == SPACE || map_data[y][x] == fill_char))
	{
		map_data[y][x] = fill_char;
		y += step;
	}
	if (map_data[y][x] == WALL)
		return (true);
	return (false);
}

static bool	validate_horizontal_wall_and_fill_space(char **map_data, size_t y, int step, char fill_char)
{
	size_t i;
	size_t end;
	size_t x;

	end = ft_strlen(map_data[y]);
	if (end == 0)
		return (false);
	i = 0;
	x = i;
	if (step < 0)
		x = end - 1;
	while (i++ < end
		&& (map_data[y][x] == SPACE || map_data[y][x] == fill_char))
	{
		map_data[y][x] = fill_char;
		x += step;
	}
	if (map_data[y][x] == WALL)
		return (true);
	return (false);
}

bool	validate_surrounded_wall_and_fill_space(char **map_data)
{
	size_t x;
	size_t y;

	y = 0;
	while (map_data[y])
	{
		if (!validate_horizontal_wall_and_fill_space(map_data, y, 1, '!')
			|| !validate_horizontal_wall_and_fill_space(map_data, y, -1, '!'))
			return (false);
		y++;
	}
	y = 0;
	x = 0;
	while (map_data[y][x])
	{
		if (!validate_vertical_wall_and_fill_space(map_data, x, 1, '!')
			|| !validate_vertical_wall_and_fill_space(map_data, x, -1, '!'))
			return (false);
		x++;
	}
	return (true);
}