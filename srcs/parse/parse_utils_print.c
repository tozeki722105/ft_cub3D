#include "parse.h"

void	print_map_list(t_map_node *ptr)
{
	while (ptr)
	{
		printf("%s\n", ptr->val);
		ptr = ptr->next;
	}
}

void	print_texture(t_loader loader)
{
	printf("north=%s;\n", loader.north_path);
	printf("south=%s;\n", loader.south_path);
	printf("west=%s;\n", loader.west_path);
	printf("east=%s;\n", loader.east_path);
	printf("floor=%d;\n", loader.floor_color);
	printf("ceiling=%d;\n", loader.ceiling_color);
}

void	print_map_player(t_loader loader)
{
	char **map;
	size_t x;
	size_t y;

	printf("x_count=%d, y_count=%d\n", loader.map_y_count, loader.map_x_count);
	map = loader.map_data;
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
	printf("player.pos.x=%lf, player.pos.y=%lf, player.angle=%lf\n", 
		loader.player_pos.x, loader.player_pos.y, loader.player_angle);
}
