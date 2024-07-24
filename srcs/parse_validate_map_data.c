/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_map_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:42:40 by toshi             #+#    #+#             */
/*   Updated: 2024/07/24 19:35:47 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_player
{
	double x;
	double y;
	double angle;
	double pdx; //視線のX成分
	double pdy; //視線のY成分
	int	side;
} t_player;

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
// 		my_perror_exit("There is an invalid element in the map", 0);
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
// 					my_perror_exit("There are multiple player elements", 0);
// 			}
// 			cur.x++;
// 		}
// 		cur.y++;
// 	}
// 	return (res);
// }


char **ft_double_str_dup(char **d_str)
{
	char **res;
	size_t	i;
	size_t	y_count;

	y_count = ft_count_rows(d_str);
	res = (char **)malloc((y_count + 1) * sizeof(char *));
	i = 0;
	while (i < y_count)
	{
		res[i] = ft_strdup(d_str[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}


#define WALL	'1'
#define SPACE	' '

bool	validate_vertical_wall_and_fill_space(char **map_data, size_t x, int step, char fill_char)
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

bool	validate_horizontal_wall_and_fill_space(char **map_data, size_t y, int step, char fill_char)
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

bool	validate_player(char **map_data, t_player *player)
{
	t_pos cur;
	// t_pos res;

	// res = (t_pos){-1, -1};
	player->y = -1;
	player->x = -1;
	cur.y = 0;
	while (map_data[cur.y])
	{
		cur.x = 0;
		while (map_data[cur.y][cur.x])
		{
			if (is_player(map_data[cur.y][cur.x]))
			{
				if (player->x == -1 && player->y == -1)
				{
					player->x = cur.x;
					player->y = cur.y;
				}
				else
					return (false);
			}
			cur.x++;
		}
		cur.y++;
	}
	if (player->x == -1 || player->y == -1)
		return (false);
	return (true);
}

double find_player_angle(char player_char)
{
	if (player_char == 'N')
		return (90);
	else if (player_char == 'S')
		return (270);
	else if (player_char == 'W')
		return (180);
	else
		return (0);
}

bool	validate_map_elements(char **map_data)
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
			{
				printf("y=%zd, x=%zd, char=%c\n", y, x, map_data[y][x]);
				return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map_data(char **map_data)
{
	char **map_cpy;
	t_player player;

	map_cpy = ft_double_str_dup(map_data);
	// validate_map_size(map_cpy);
	if (!validate_surrounded_wall_and_fill_space(map_cpy))
		my_perror_exit("The map is not surrounded by walls", 0);
	if (!validate_player(map_cpy, &player))
		my_perror_exit("Please put only one player element in the map", 0);
	player.angle = find_player_angle(map_cpy[(int)player.y][(int)player.x]);
	if (!validate_map_elements(map_cpy)) //壁の中身が0/1/N/S/W/Eだけかどうか
		my_perror_exit("error", 0);
	free_
	return (true);
}