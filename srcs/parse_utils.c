#include "parse.h"

void	my_perror_exit(char *err_s, int exit_code)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	exit(exit_code);
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

bool	ft_isequal(char *s1, char *s2)
{
	size_t len;

	len = ft_strlen(s1);
	return (len == ft_strlen(s2) && ft_strncmp(s1, s2, len) == 0);
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

//\tは入れない方針
bool	is_map_element(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ');
}

bool	is_map_element_strictly(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '!');
}

void	free_map_node(t_map_node *map_node)
{
	free(map_node->val);
	free(map_node);
}

void	free_map_node_list(t_map_node *ptr)
{
	t_map_node *next_ptr;

	if (!ptr)
		return ;
	next_ptr = ptr->next;
	while (next_ptr)
	{
		free_map_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_map_node(ptr);
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

void	free_loader(t_loader loader)
{
	free(loader.north_path);
	free(loader.south_path);
	free(loader.west_path);
	free(loader.east_path);
	size_t i =0;
	while (loader.map_data[i])
		free(loader.map_data[i++]);
	free(loader.map_data);
	free_map_node_list(loader.map_head);
}

t_map_node *make_new_map_node(char *str)
{
	t_map_node *new;

	
	new = (t_map_node *)malloc(sizeof(t_map_node));
	new->val = str;
	new->next = NULL;
	return (new);
}

t_map_node *find_last_map_node(t_map_node *ptr)
{
	while(ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void add_last_map_node(t_map_node **head, t_map_node *new)
{
	if (!(*head))
	{
		*head = new;
		return ;
	}
	find_last_map_node(*head)->next = new;
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

t_loader init_loader()
{
	t_loader	loader;

	loader.kind = KIND_DEFAULT;
	loader.prev_kind = KIND_DEFAULT;
	loader.north_path = NULL;
	loader.south_path = NULL;
	loader.west_path = NULL;
	loader.east_path = NULL;
	loader.floor_color = -1;
	loader.ceiling_color = -1;
	loader.map_head = NULL;
	loader.map_data = NULL;
	loader.player_pos = (t_pos){-1, -1};
	return (loader);
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

size_t ft_count_rows(char **d_str)
{
	size_t i;

	i = 0;
	while (d_str[i])
		i++;
	return (i);
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


bool	is_member_default(t_loader loader, t_parse_kind kind)
{
	if (kind == KIND_NORTH)
		return (loader.north_path == NULL);
	if (kind == KIND_SOUTH)
		return (loader.south_path == NULL);
	if (kind == KIND_WEST)
		return (loader.west_path == NULL);
	if (kind == KIND_EAST)
		return (loader.east_path == NULL);
	if (kind == KIND_FLOOR)
		return (loader.floor_color == -1);
	if (kind == KIND_CEILING)
		return (loader.ceiling_color == -1);
	if (kind == KIND_MAP)
		return (loader.map_data == NULL);
	else
		return (true);
}

bool	is_textures_full(t_loader loader)
{
	return (loader.north_path && loader.south_path
		&& loader.west_path && loader.east_path
		&& loader.floor_color > -1 && loader.ceiling_color > -1);
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

void	add_wall(t_loader *loader, t_parse_kind kind, char *str)
{
	char *val;

	val = extract_val(str, kind);
	if (kind == KIND_NORTH)
		loader->north_path = val;
	else if (kind == KIND_SOUTH)
		loader->south_path = val;
	else if (kind == KIND_WEST)
		loader->west_path = val;
	else if (kind == KIND_EAST)
		loader->east_path = val;
}

void	add_color(t_loader *loader, t_parse_kind kind, char *str)
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
		loader->floor_color = color;
	else if (kind == KIND_CEILING)
		loader->ceiling_color = color;
}

void	print_map_node(t_map_node *ptr)
{
	while (ptr)
	{
		printf("%s\n", ptr->val);
		ptr = ptr->next;
	}
}

static t_map_node *find_prev_of_first(t_map_node *ptr, char *trimed_node_val)
{
	t_map_node *prev;
	t_map_node *head = ptr;

	prev = NULL;
	while (ptr && ft_isequal(ptr->val, trimed_node_val))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	// if (!prev)
	// 	return (head);
	return (prev);
}

static t_map_node *find_last(t_map_node *ptr, char *trimed_node_val)
{
	t_map_node *next_ptr;

	while (next_ptr)
	{
		if (!ft_isequal(ptr->val, trimed_node_val)
			&& ft_isequal(next_ptr->val, trimed_node_val))
		{
			while (next_ptr && ft_isequal(next_ptr->val, trimed_node_val))
				next_ptr = next_ptr->next;
			if (!next_ptr)
				return (ptr);
		}
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	return (ptr);
}

void	trim_map_list(t_map_node **head, char *trimed_node_val)
{
	t_map_node *prev_of_first;
	t_map_node *last;
	t_map_node *first;

	if (!head || !(*head) || !((*head)->next))
		return ;
	prev_of_first = find_prev_of_first(*head, trimed_node_val);
	last = find_last(*head, trimed_node_val);
	if (prev_of_first)
	{
		
		first = prev_of_first->next;
		prev_of_first->next = NULL;
		free_map_node_list(*head);
		*head = first;
	}
	free_map_node_list(last->next);
	last->next = NULL;
}

bool	is_contained_newline(t_map_node *ptr)
{
	while (ptr && !ft_isequal(ptr->val, ""))
		ptr = ptr->next;
	if (ptr)
		return (true);
	return (false);
}


static size_t	get_start_count(const char *s1, const char *set)
{
	size_t	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static size_t	get_end_count(const char *s1, const char *set, size_t start)
{
	size_t	len;

	if (set == NULL)
		return (ft_strlen(s1) - 1);
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len -1]) != NULL)
		len--;
	return (len - 1);
}

char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set, const char *back_trim_set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (front_trim_set == NULL && back_trim_set == NULL)
		return ((char *)s1);
	start = get_start_count(s1, front_trim_set);
	end = get_end_count(s1, back_trim_set, start);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(&s1[start], 0, end - start + 1));
}