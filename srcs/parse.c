#include "ogv1.h"
#include "parse.h"
#include "calc.h"

void	print_map(char **map_data);

void	my_perror_exit(char *err_s, int exit_code)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	exit(exit_code);
}

bool	ft_isequal(char *s1, char *s2)
{
	size_t len;

	len = ft_strlen(s1);
	return (len == ft_strlen(s2) && ft_strncmp(s1, s2, len) == 0);
}

// path/extentionにNULLが来ない前提の実装
bool	validate_extention(char *path, char *extention)
{
	char *ptr;

	ptr = ft_strrchr(path, *extention);
	if (!ptr || ptr == path)
		return (false);
	return (ft_isequal(ptr, extention));
}

//\tは入れない方針
bool	is_map_element(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ');
}

//スペースだけの文字列もmapのデータの一部として見做されてしまう
bool	is_map_str(char *str)
{
	// if (*str == '\n')
	// 	return (false);
	while (*str && *str != '\n')
	{
		if (!is_map_element(*str))
			return (false);
		str++;
	}
	return (true);
}

t_parse_kind	parse_kind(char *str)
{
	if (*str == '\n')
		return (KIND_NEWLINE);
	if (is_map_str(str))
		return (KIND_MAP);
	if (*str == 'N' && *(str + sizeof(char)) == 'O')
		return (KIND_NORTH);
	if (*str == 'S' && *(str + sizeof(char)) == 'O')
		return (KIND_SOUTH);
	if (*str == 'W' && *(str + sizeof(char)) == 'E')
		return (KIND_WEST);
	if (*str == 'E' && *(str + sizeof(char)) == 'A')
		return (KIND_EAST);
	if (*str == 'F')
		return (KIND_FLOOR);
	if (*str == 'C')
		return (KIND_CEILING);
	else
		return (KIND_FALSE);//不正な識別子が混ざっている
}

t_reader init_reader()
{
	t_reader reader;

	reader.north_path = NULL;
	reader.south_path = NULL;
	reader.west_path = NULL;
	reader.east_path = NULL;
	reader.floor_color = -1;
	reader.ceiling_color = -1;
	reader.map_data = NULL;
	reader.player_x = -1;
	reader.player_y = -1;
	return (reader);
}

bool	is_kindval_default(t_reader reader, t_parse_kind kind)
{
	if (kind == KIND_NORTH)
		return (reader.north_path == NULL);
	if (kind == KIND_SOUTH)
		return (reader.south_path == NULL);
	if (kind == KIND_WEST)
		return (reader.west_path == NULL);
	if (kind == KIND_EAST)
		return (reader.east_path == NULL);
	if (kind == KIND_FLOOR)
		return (reader.floor_color == -1);
	if (kind == KIND_CEILING)
		return (reader.ceiling_color == -1);
	if (kind == KIND_MAP)
		return (reader.map_data == NULL);
	else
		return (true);
}

bool	is_wall(t_parse_kind kind)
{
	return (kind == KIND_NORTH || kind == KIND_SOUTH || kind == KIND_WEST || kind == KIND_EAST);
}

bool	is_view_background(t_parse_kind kind)
{
	return (kind == KIND_FLOOR || kind == KIND_CEILING);
}

bool	is_texture(t_parse_kind kind)
{
	return (is_wall(kind) || is_view_background(kind));
}

int make_rgb_color(int r, int g, int b)
{
	int res;

	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	res = r;
	res <<= 8;
	res += g;
	res <<= 8;
	res += b;
	return (res);
}

char *extract_val(char *str, t_parse_kind kind)
{
	size_t	identifer_len;
	char	*val_include_space;
	char	*val;

	if (is_wall(kind))
		identifer_len = 2;
	else
		identifer_len = 1;
	val_include_space = ft_substr(str, identifer_len, ft_strlen(str) - identifer_len);
	val = ft_strtrim(val_include_space, " \t\n");
	free(val_include_space);
	return (val);
}

int convert_rgb_color(char *color_str)
{
	int *rgb;
	int res;
	int i;
	char *sep_ptr;
	char *sub_s;

	rgb = (int *)malloc(sizeof(int) * 3);
	i = 0;
	while (i < 3)
	{
		if (i == 2)
			sep_ptr = ft_strchr(color_str, '\0');
		else
			sep_ptr = ft_strchr(color_str, ',');
		if (!sep_ptr)
			my_perror_exit("Not enough RGB values", 0);
		sub_s = ft_substr(color_str, 0, (size_t)(sep_ptr - color_str));
		rgb[i++] = ft_atoi(sub_s);
		free(sub_s);
		color_str = sep_ptr + sizeof(char);
	}
	res = make_rgb_color(rgb[0], rgb[1], rgb[2]);
	free(rgb);
	return (res);
}

void	add_wall(t_reader *reader, t_parse_kind kind, char *str)
{
	char *val;

	val = extract_val(str, kind);
	if (kind == KIND_NORTH)
		reader->north_path = val;
	else if (kind == KIND_SOUTH)
		reader->south_path = val;
	else if (kind == KIND_WEST)
		reader->west_path = val;
	else if (kind == KIND_EAST)
		reader->east_path = val;
}

void	add_color(t_reader *reader, t_parse_kind kind, char *str)
{
	char *val;
	int color;

	val = extract_val(str, kind);
	//.や-など不要な文字が入ってないか確認
	color = convert_rgb_color(val);
	free(val);
	if (color == -1)
		my_perror_exit("RGB contains values ​​other than 0 to 255", 0);
	if (kind == KIND_FLOOR)
		reader->floor_color = color;
	else if (kind == KIND_CEILING)
		reader->ceiling_color = color;
}

bool	is_textures_full(t_reader reader)
{
	return (reader.north_path && reader.south_path && reader.west_path && reader.east_path
		&& reader.floor_color > -1 && reader.ceiling_color > -1);
}

t_mnode *make_new_mnode(char *str)
{
	t_mnode *new;

	new = (t_mnode *)malloc(sizeof(t_mnode));
	new->val = str;
	new->next = NULL;
	return (new);
}

t_mnode *find_last_mnode(t_mnode *ptr)
{
	while(ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void add_last_mnode(t_mnode **head, t_mnode *new)
{
	if (!(*head))
	{
		*head = new;
		return ;
	}
	find_last_mnode(*head)->next = new;
}

t_mnode *make_mnode_list(char *str, int fd)
{
	t_mnode *head;
	t_mnode *new;
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
		new = make_new_mnode(val);
		add_last_mnode(&head, new);
		free(str);
	}
	return (head);
}

size_t count_map_size(t_mnode *ptr, size_t *map_y_count)
{
	size_t map_x_count;
	size_t ptr_len;
	
	map_x_count = 0;
	*map_y_count = 0;
	while (ptr)
	{
		ptr_len = ft_strlen(ptr->val);
		if (map_x_count < ptr_len)
			map_x_count = ptr_len;
		ptr = ptr->next;
		(*map_y_count)++;
	}
	return (map_x_count);
}

char **create_map(t_mnode *ptr)
{
	size_t	map_x_count;
	size_t	map_y_count;
	char **map;
	size_t i;

	map_x_count = count_map_size(ptr, &map_y_count);
	map = (char **)malloc(sizeof(char *) * (map_y_count + 1));
	i = 0;
	while (i < map_y_count)
	{
		map[i] = (char *)malloc(sizeof(char) * (map_x_count + 1));
		ft_memset(map[i], ' ', map_x_count);
		ft_memmove(map[i], ptr->val, ft_strlen(ptr->val));
		map[i][map_x_count] = '\0';
		i++;
		ptr = ptr->next;
	}
	map[i] = NULL;
	return (map);
}

void	free_mnode(t_mnode *mnode)
{
	free(mnode->val);
	free(mnode);
}

void	free_mnode_list(t_mnode *ptr)
{
	t_mnode *next_ptr;

	if (!ptr)
		return ;
	next_ptr = ptr->next;
	while (next_ptr)
	{
		free_mnode(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_mnode(ptr);
}

size_t count_map_content_size(char *map_row)
{
	size_t i;

	i = 0;
	while (map_row[i])
	{
		if ()
	}
}

bool validate_map_size(size_t map_y_count, t_mnode *ptr)
{
	size_t map_content_size;

	if (map_y_count < 3)
		return (false);
	map_content_size = 0;
	while (ptr)
	{
		if ()
		ptr = ptr->next;
	}
	
}

void	add_map(t_reader *reader, char *str, int fd)
{
	t_mnode *head;
	char **map;
	// size_t	map_x_count;
	// size_t	map_y_count;

	head = make_mnode_list(str, fd);
	// map_x_count = count_map_size(head, &map_y_count);
	// validate_map_size(map_y_count, head);
	map = create_map(head);
	free_mnode_list(head);
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

size_t count_y(char **d_str)
{
	size_t i;

	i = 0;
	while (d_str[i])
		i++;
	return (i);
}

char **ft_double_str_dup(char **d_str)
{
	char **res;
	size_t	i;
	size_t	y_count;

	y_count = count_y(d_str);
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

	end = count_y(map_data);
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
		return (false);
	i = 0;
	x = i;
	if (step < 0)
		x = end - 1;
	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
	{
		map_data[y][x] = '!';
		x += step;
	}
	if (map_data[y][x] == '1')
		return (true);
	return (false);
}

void	fill_y_space_until_wall(char **map_data, size_t x, int step)
{
	size_t i;
	size_t end;
	size_t y;

	end = count_y(map_data);
	if (end == 0)
		return (false);
	i = 0;
	y = i;
	if (step < 0)
		y = end - 1;
	while (i++ < end && (map_data[y][x] == ' ' || map_data[y][x] == '!'))
	{
		map_data[y][x] = '!';
		y += step;
	}
	if (map_data[y][x] == '1')
		return (true);
	return (false);
}


bool	is_player(char **map_data, t_pos cur)
{
	return (map_data[cur.y][cur.x] == 'N' || map_data[cur.y][cur.x] == 'S' 
		|| map_data[cur.y][cur.x] == 'E' || map_data[cur.y][cur.x] == 'W');
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
			if (is_player(map_data, cur))
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
	// validate_map_size(map_cpy);
	if (!validate_surrounded_wall(map_cpy))
		my_perror_exit("The map is not surrounded by walls", 0);;
	player = search_player(map_cpy);
	if (player.x == -1 || player.y == -1)
		my_perror_exit("The player element was not found", 0);
	map_cpy[player.y][player.x] = '0';
	// validate_map_elements
	//壁の中身が0/1/N/S/W/Eだけかどうか
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

void	print_texture(t_reader reader)
{
	printf("north=%s;\n", reader.north_path);
	printf("south=%s;\n", reader.south_path);
	printf("west=%s;\n", reader.west_path);
	printf("east=%s;\n", reader.east_path);
	printf("floor=%d;\n", reader.floor_color);
	printf("ceiling=%d;\n", reader.ceiling_color);
}
void	print_map(char **map_data)
{
	char **map;
	size_t x;
	size_t y;

	map = map_data;
	y = 0;
	while (map[y])
	{
		x=0;
		while (map[y][x])
		{
			if (map[y][x] == '\n')
				printf("[n->]");
			printf("%c", map[y][x]);
			x++;
		}
		printf(";\n");
		y++;
	}
}

void	free_reader(t_reader reader)
{
	free(reader.north_path);
	free(reader.south_path);
	free(reader.west_path);
	free(reader.east_path);
	size_t i =0;
	while (reader.map_data[i])
		free(reader.map_data[i++]);
	free(reader.map_data);
}

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q a.out");
// }

int main(int argc, char **argv)
{
	t_reader reader;

	reader = parse(argv[1]);
	print_texture(reader);
	print_map(reader.map_data);
	free_reader(reader);
	// printf("%d, %d\n", make_rgb_color(220, 100, 0), 0xFF1E00);
}