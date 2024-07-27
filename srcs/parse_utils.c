#include "parse.h"

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

void	free_loader(t_loader loader)
{
	free(loader.north_path);
	free(loader.south_path);
	free(loader.west_path);
	free(loader.east_path);
	free_map_node_list(loader.map_head);
	ft_free_double_str(loader.map_data);
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









// void	free_reader(t_reader reader)
// {
// 	free(reader.north_path);
// 	free(reader.south_path);
// 	free(reader.west_path);
// 	free(reader.east_path);
// 	size_t i =0;
// 	while (reader.map_data[i])
// 		free(reader.map_data[i++]);
// 	free(reader.map_data);
// }


// t_reader init_reader()
// {
// 	t_reader reader;

// 	reader.north_path = NULL;
// 	reader.south_path = NULL;
// 	reader.west_path = NULL;
// 	reader.east_path = NULL;
// 	reader.floor_color = -1;
// 	reader.ceiling_color = -1;
// 	reader.map_data = NULL;
// 	reader.player_x = -1;
// 	reader.player_y = -1;
// 	return (reader);
// }









// int convert_rgb_color(char *color_str)
// {
// 	int *rgb;
// 	int res;
// 	int i;
// 	char *sep_ptr;
// 	char *sub_s;

// 	rgb = (int *)malloc(sizeof(int) * 3);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (i == 2)
// 			sep_ptr = ft_strchr(color_str, '\0');
// 		else
// 			sep_ptr = ft_strchr(color_str, ',');
// 		if (!sep_ptr)
// 			ft_perror_exit("Not enough RGB values", 0);
// 		sub_s = ft_substr(color_str, 0, (size_t)(sep_ptr - color_str));
// 		rgb[i++] = ft_atoi(sub_s);
// 		free(sub_s);
// 		color_str = sep_ptr + sizeof(char);
// 	}
// 	res = make_rgb_color(rgb[0], rgb[1], rgb[2]);
// 	free(rgb);
// 	return (res);
// }