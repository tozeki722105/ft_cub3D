#include "parse.h"

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
		return (ft_perror_ret_false("The map size is too small"));
	map_cpy = ft_double_str_dup(map_data);
	if (!validate_surrounded_wall_and_fill_space(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (ft_perror_ret_false("The map is not surrounded by walls"));
	}
	if (!validate_map_elements(map_cpy))
	{
		ft_free_double_str(map_cpy);
		return (ft_perror_ret_false("There is space in the map area"));
	}
	ft_free_double_str(map_cpy);
	return (true);
}


// bool	validate_x_first_wall(char **map_data, size_t y, int step)
// {
// 	size_t i;
// 	size_t end;
// 	size_t x;

// 	end = ft_strlen(map_data[y]);
// 	if (end == 0)
// 		return (false);
// 	i = 0;
// 	x = i;
// 	if (step < 0)
// 		x = end - 1;
// 	while (i++ < end && map_data[y][x] == ' ')
// 		x += step;
// 	if (map_data[y][x] == '1')
// 		return (true);
// 	return (false);
// }

// bool	validate_y_first_wall(char **map_data, size_t x, int step)
// {
// 	size_t i;
// 	size_t end;
// 	size_t y;

// 	end = ft_count_rows(map_data);
// 	if (end == 0)
// 		return (false);
// 	i = 0;
// 	y = i;
// 	if (step < 0)
// 		y = end - 1;
// 	while (i++ < end && map_data[y][x] == ' ')
// 		y += step;
// 	if (map_data[y][x] == '1')
// 		return (true);
// 	return (false);
// }


// bool	validate_surrounded_wall(char **map_data)
// {
// 	size_t x;
// 	size_t y;

// 	y = 0;
// 	while (map_data[y])
// 	{
// 		if (!validate_x_first_wall(map_data, y, 1)
// 			|| validate_x_first_wall(map_data, y, -1))
// 			return (false);
// 		y++;
// 	}
// 	y = 0;
// 	x = 0;
// 	while (map_data[y][x])
// 	{
// 		if (!validate_y_first_wall(map_data, x, 1)
// 			|| !validate_y_first_wall(map_data, x, -1))
// 			return (false);
// 		x++;
// 	}
// 	return (true);
// }

// void	fill_x_space_until_wall(char **map_data, size_t y, int step, char fill_char)
// {
// 	size_t i;
// 	size_t end;
// 	size_t x;

// 	end = ft_strlen(map_data[y]);
// 	if (end == 0)
// 		return ;
// 	i = 0;
// 	x = i;
// 	if (step < 0)
// 		x = end - 1;
// 	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
// 	{
// 		map_data[y][x] = '!';
// 		x += step;
// 	}
// 	return ;
// }


// void	fill_y_space_until_wall(char **map_data, size_t x, int step)
// {
// 	size_t i;
// 	size_t end;
// 	size_t y;

// 	end = ft_count_rows(map_data);
// 	if (end == 0)
// 		return ;
// 	i = 0;
// 	y = i;
// 	if (step < 0)
// 		y = end - 1;
// 	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
// 	{
// 		map_data[y][x] = '!';
// 		y += step;
// 	}
// 	return ;
// }





// bool	validate_map_elements_helper(char **map_data)
// {
// 	size_t y;
// 	size_t x;

// 	y = 0;
// 	while (map_data[y])
// 	{
// 		x = 0;
// 		while (map_data[y][x])
// 		{
// 			// if (!is_map_element_strictly(map_data[y][x]))
// 			if (map_data[y][x] == '!'
// 				|| (map_data[y][x] != ' '
// 				&& !is_map_element(map_data[y][x])))
// 				return (false);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

// bool	validate_map_elements(char **map_data)
// {
// 	size_t x;
// 	size_t y;

// 	y = 0;
// 	while (map_data[y])
// 	{
// 		fill_x_space_until_wall(map_data, y, 1);
// 		fill_x_space_until_wall(map_data, y, -1);
// 		y++;
// 	}
// 	y = 0;
// 	x = 0;
// 	while (map_data[y][x])
// 	{
// 		fill_y_space_until_wall(map_data, x, 1);
// 		fill_y_space_until_wall(map_data, x, -1);
// 		x++;
// 	}
// 	if (!validate_map_elements_helper(map_data))
// 		ft_perror_exit("There is an invalid element in the map", 0);
// 	return (true);
// }


// t_pos search_player(char **map_data)
// {
// 	t_pos cur;
// 	t_pos res;

// 	res.x = -1;
// 	res.y = -1;
// 	cur.y = 0;
// 	while (map_data[cur.y])
// 	{
// 		cur.x = 0;
// 		while (map_data[cur.y][cur.x])
// 		{
// 			if (is_player(map_data[cur.y][cur.x]))
// 			{
// 				if (res.x == -1 && res.y == -1)
// 					res = cur;
// 				else
// 					ft_perror_exit("There are multiple player elements", 0);
// 			}
// 			cur.x++;
// 		}
// 		cur.y++;
// 	}
// 	return (res);
// }


// static bool	validate_player_pos(char **map_data, t_pos *player)
// {
// 	t_pos cur;

// 	cur.y = 0;
// 	while (map_data[(int)cur.y])
// 	{
// 		cur.x = 0;
// 		while (map_data[(int)cur.y][(int)cur.x])
// 		{
// 			if (is_player(map_data[(int)cur.y][(int)cur.x]))
// 			{
// 				if (player->x == -1 && player->y == -1)
// 					*player = cur;
// 				else
// 					return (false);
// 			}
// 			cur.x++;
// 		}
// 		cur.y++;
// 	}
// 	if (player->x == -1 || player->y == -1)
// 		return (false);
// 	return (true);
// }

// static double find_player_angle(char **map_data, t_pos pos)
// {
// 	if (map_data[(int)pos.y][(int)pos.x] == 'N')
// 		return (90);
// 	else if (map_data[(int)pos.y][(int)pos.x] == 'S')
// 		return (270);
// 	else if (map_data[(int)pos.y][(int)pos.x] == 'W')
// 		return (180);
// 	else
// 		return (0);
// }


