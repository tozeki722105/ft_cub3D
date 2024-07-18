#include "ogv1.h"
#include "parse.h" 

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
			exit(0);//rgb値がたらない
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
		exit(0);//rgb0~255ではない
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
			exit(0);//不正な情報が入っている
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

void	add_map(t_reader *reader, char *str, int fd)
{
	t_mnode *head;
	char **map;

	head = make_mnode_list(str, fd);
	map = create_map(head);
	free_mnode_list(head);
	reader->map_data = map;
}

void	add_data(char *str, t_parse_kind kind, int fd, t_reader *reader)
{
	if (!is_kindval_default(*reader, kind))
		exit(0);//重複している引数
	if (is_wall(kind))
		add_wall(reader, kind, str);
	else if (is_view_background(kind))
		add_color(reader, kind, str);
	else if (kind == KIND_MAP)
	{
		if (!is_textures_full(*reader))
			exit(0); //マップの前の要素が全て揃っていない
		add_map(reader, str, fd);
	}
	else if (kind == KIND_NEWLINE)
		return ;
	else
		exit(0);//不正な識別子が混ざっている
}

t_reader	parse(char *path)
{
	int				fd;
	char			*str;
	t_reader		reader;

	reader = init_reader();
	if (!validate_extention(path, ".cub"))
		exit (0); //拡張子が違う
	fd = open(path, O_RDONLY);
	if (fd == SYSERR)
		exit (0); //openエラー
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		add_data(str, parse_kind(str), fd, &reader);
		free(str);
	}
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
void	print_map(t_reader reader)
{
	char **map;
	size_t x;
	size_t y;

	map = reader.map_data;
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

__attribute__((destructor))
static void destructor() {
   system("leaks -q a.out");
}

int main(int argc, char **argv)
{
	t_reader reader;

	reader = parse(argv[1]);
	print_texture(reader);
	print_map(reader);
	free_reader(reader);
	// printf("%d, %d\n", make_rgb_color(220, 100, 0), 0xFF1E00);
}