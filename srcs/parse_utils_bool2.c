#include "parse.h"

bool	is_texture(t_parse_kind kind)
{
	return (is_wall(kind) || is_background(kind));
}

/// @brief sapace_only_str is true 
bool	is_map_str(char *str)
{
	if (*str == '\n')
		return (false);
	while (*str && *str != '\n')
	{
		if (!is_map_element(*str))
			return (false);
		str++;
	}
	return (true);
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
		return (false);
}

bool	is_textures_full(t_loader loader)
{
	return (loader.north_path && loader.south_path
		&& loader.west_path && loader.east_path
		&& loader.floor_color > -1 && loader.ceiling_color > -1);
}