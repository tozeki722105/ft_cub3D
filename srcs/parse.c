#include "ogv1.h"
#include "parse.h"
#include "calc.h"






// bool	is_kindval_default(t_reader reader, t_parse_kind kind)
// {
// 	if (kind == KIND_NORTH)
// 		return (reader.north_path == NULL);
// 	if (kind == KIND_SOUTH)
// 		return (reader.south_path == NULL);
// 	if (kind == KIND_WEST)
// 		return (reader.west_path == NULL);
// 	if (kind == KIND_EAST)
// 		return (reader.east_path == NULL);
// 	if (kind == KIND_FLOOR)
// 		return (reader.floor_color == -1);
// 	if (kind == KIND_CEILING)
// 		return (reader.ceiling_color == -1);
// 	if (kind == KIND_MAP)
// 		return (reader.map_data == NULL);
// 	else
// 		return (true);
// }

// bool	is_wall(t_parse_kind kind)
// {
// 	return (kind == KIND_NORTH || kind == KIND_SOUTH || kind == KIND_WEST || kind == KIND_EAST);
// }

// bool	is_view_background(t_parse_kind kind)
// {
// 	return (kind == KIND_FLOOR || kind == KIND_CEILING);
// }

// bool	is_texture(t_parse_kind kind)
// {
// 	return (is_wall(kind) || is_view_background(kind));
// }



// bool	is_textures_full(t_reader reader)
// {
// 	return (reader.north_path && reader.south_path && reader.west_path && reader.east_path
// 		&& reader.floor_color > -1 && reader.ceiling_color > -1);
// }



t_map_node *make_map_node_list(char *str, int fd)
{
	t_map_node *head;
	t_map_node *new;
	char *val;
	t_parse_kind kind;
	
	head = NULL;
	while (1)
	{
		if (!head)
			str = ft_strdup(str);
		else
			str = get_next_line(fd);
		if (!str)
			break;
		kind = parse_kind(str);
		if (kind == KIND_NEWLINE)
		{
			free(str);
			break ;
		}	
		if (kind != KIND_MAP)
			my_perror_exit("There is invalid information in the map data", 0);
		val = ft_strtrim(str, "\n");
		new = make_new_map_node(val);
		add_last_map_node(&head, new);
		free(str);
	}
	return (head);
}





// size_t count_map_content_size(char *map_row)
// {
// 	size_t i;

// 	i = 0;
// 	while (map_row[i])
// 	{
// 		if ()
// 	}
// }

// bool validate_map_size(size_t map_y_count, t_map_node *ptr)
// {
// 	size_t map_content_size;

// 	if (map_y_count < 3)
// 		return (false);
// 	map_content_size = 0;
// 	while (ptr)
// 	{
// 		if ()
// 		ptr = ptr->next;
// 	}
	
// }

void	add_map(t_reader *reader, char *str, int fd)
{
	t_map_node *head;
	char **map;
	// size_t	map_x_count;
	// size_t	map_y_count;

	head = make_map_node_list(str, fd);
	// map_x_count = count_map_size(head, &map_y_count);
	// validate_map_size(map_y_count, head);
	map = create_map(head);
	free_map_node_list(head);
	reader->map_data = map;
}

void	add_data(char *str, t_parse_kind kind, int fd, t_reader *reader)
{
	if (!is_kindval_default(*reader, kind))
		my_perror_exit("Duplicate elements", 0);
	if (is_wall(kind))
		add_wall(reader, kind, str);
	else if (is_view_background(kind))
		add_color(reader, kind, str);
	else if (kind == KIND_MAP)
	{
		if (!is_textures_full(*reader))
			my_perror_exit("Missing texture or background element", 0);
		add_map(reader, str, fd);
	}
	else if (kind == KIND_NEWLINE)
		return ;
	else
		my_perror_exit("Contains invalid elements", 0);
}



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

bool	validate_x_first_wall(char **map_data, size_t y, int step)
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
	while (i++ < end && map_data[y][x] == ' ')
		x += step;
	if (map_data[y][x] == '1')
		return (true);
	return (false);
}

bool	validate_y_first_wall(char **map_data, size_t x, int step)
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
	while (i++ < end && map_data[y][x] == ' ')
		y += step;
	if (map_data[y][x] == '1')
		return (true);
	return (false);
}


bool	validate_surrounded_wall(char **map_data)
{
	size_t x;
	size_t y;

	y = 0;
	while (map_data[y])
	{
		if (!validate_x_first_wall(map_data, y, 1)
			|| validate_x_first_wall(map_data, y, -1))
			return (false);
		y++;
	}
	y = 0;
	x = 0;
	while (map_data[y][x])
	{
		if (!validate_y_first_wall(map_data, x, 1)
			|| !validate_y_first_wall(map_data, x, -1))
			return (false);
		x++;
	}
	return (true);
}

void	fill_x_space_until_wall(char **map_data, size_t y, int step)
{
	size_t i;
	size_t end;
	size_t x;

	end = ft_strlen(map_data[y]);
	if (end == 0)
		return ;
	i = 0;
	x = i;
	if (step < 0)
		x = end - 1;
	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
	{
		map_data[y][x] = '!';
		x += step;
	}
	return ;
}

void	fill_y_space_until_wall(char **map_data, size_t x, int step)
{
	size_t i;
	size_t end;
	size_t y;

	end = ft_count_rows(map_data);
	if (end == 0)
		return ;
	i = 0;
	y = i;
	if (step < 0)
		y = end - 1;
	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
	{
		map_data[y][x] = '!';
		y += step;
	}
	return ;
}



bool	validate_map_elements_helper(char **map_data)
{
	size_t y;
	size_t x;

	y = 0;
	while (map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			if (!is_map_element_strictly(map_data[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map_elements(char **map_data)
{
	size_t x;
	size_t y;

	y = 0;
	while (map_data[y])
	{
		fill_x_space_until_wall(map_data, y, 1);
		fill_x_space_until_wall(map_data, y, -1);
		y++;
	}
	y = 0;
	x = 0;
	while (map_data[y][x])
	{
		fill_y_space_until_wall(map_data, x, 1);
		fill_y_space_until_wall(map_data, x, -1);
		x++;
	}
	if (!validate_map_elements_helper(map_data))
		my_perror_exit("There is an invalid element in the map", 0);
	return (true);
}


t_pos search_player(char **map_data)
{
	t_pos cur;
	t_pos res;

	res.x = -1;
	res.y = -1;
	cur.y = 0;
	while (map_data[cur.y])
	{
		cur.x = 0;
		while (map_data[cur.y][cur.x])
		{
			if (is_player(map_data[cur.y][cur.x]))
			{
				if (res.x == -1 && res.y == -1)
					res = cur;
				else
					my_perror_exit("There are multiple player elements", 0);
			}
			cur.x++;
		}
		cur.y++;
	}
	return (res);
}


void	validate_map_data(char **map_data)
{
	char **map_cpy;
	t_pos player;

	map_cpy = ft_double_str_dup(map_data);
	validate_map_elements(map_cpy); //壁の中身が0/1/N/S/W/Eだけかどうか
	print_map(map_cpy);
	// validate_map_size(map_cpy);
	// if (!validate_surrounded_wall(map_cpy))
	// 	my_perror_exit("The map is not surrounded by walls", 0);;
	// player = search_player(map_cpy);
	// if (player.x == -1 || player.y == -1)
	// 	my_perror_exit("The player element was not found", 0);
	// map_cpy[player.y][player.x] = '0';
}

t_reader	parse(char *path)
{
	int				fd;
	char			*str;
	t_reader		reader;

	reader = init_reader();
	if (!validate_extention(path, ".cub"))
		my_perror_exit("The file extension is different", 0);
	fd = open(path, O_RDONLY);
	if (fd == SYSERR)
		my_perror_exit("A system call failed", 0);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		add_data(str, parse_kind(str), fd, &reader);
		free(str);
	}
	validate_map_data(reader.map_data);
	return (reader);
}

