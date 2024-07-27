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

/// @param path not NULL
/// @param extention not NULL (.)start
bool	validate_extention(char *path, char *extention)
{
	char *ptr;

	ptr = ft_strrchr(path, *extention);
	if (!ptr || ptr == path)
		return (false);
	return (ft_isequal(ptr, extention));
}

static bool	is_contained_newline(t_map_node *ptr)
{
	while (ptr && !ft_isequal(ptr->val, ""))
		ptr = ptr->next;
	if (ptr)
		return (true);
	return (false);
}

static size_t count_map_size(t_map_node *ptr, size_t *map_y_count)
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

static char **convert_map_data(t_map_node *ptr)
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

t_loader	parse(char *path)
{
	t_loader		loader;
	int				fd;

	if (!validate_extention(path, ".cub"))
		ft_perror_exit("The file extension is different", 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_perror_exit("A system call failed", 0);
	loader = init_loader();
	load_textures(fd, &loader);
	load_map_list(fd, &loader);
	trim_map_list(&(loader.map_head), "");
	if (is_contained_newline(loader.map_head))
		ft_perror_exit("Only one map_data is allowed", 0);
	loader.map_data = convert_map_data(loader.map_head);
	if (!validate_map_data(loader.map_data))
		exit(0);
	close(fd);
	return (loader);
}

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q a.out");
// }

int main(int argc, char **argv)
{
	// t_reader reader;

	parse(argv[1]);
	// reader = parse(argv[1]);
	// print_texture(reader);
	// print_map(reader.map_data);
	// free_reader(reader);
	// printf("%d, %d\n", make_rgb_color(220, 100, 0), 0xFF1E00);
}