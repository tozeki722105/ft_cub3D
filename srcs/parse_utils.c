#include "parse.h"

t_loader init_loader()
{
	t_loader	loader;

	loader.north_path = NULL;
	loader.south_path = NULL;
	loader.west_path = NULL;
	loader.east_path = NULL;
	loader.floor_color = -1;
	loader.ceiling_color = -1;
	loader.map_head = NULL;
	loader.map_data = NULL;
	loader.player_grid_pos = (t_pos){-1, -1};
	loader.player_pos = (t_pos){-1, -1};
	return (loader);
}
