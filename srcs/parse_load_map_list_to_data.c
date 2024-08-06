#include "parse.h"

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

void load_map_list_to_data(t_map_node *ptr, t_loader *loader)
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
	loader->map_data = map;
	loader->map_y_count = map_y_count;
	loader->map_x_count = map_x_count;
}