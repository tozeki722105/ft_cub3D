#include "parse.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/// @brief \t not true 
bool	is_map_element(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

bool	is_wall(t_line_kind kind)
{
	return (kind == KIND_NORTH || kind == KIND_SOUTH || kind == KIND_WEST || kind == KIND_EAST);
}

bool	is_background(t_line_kind kind)
{
	return (kind == KIND_FLOOR || kind == KIND_CEILING);
}

bool	is_texture(t_line_kind kind)
{
	return (is_wall(kind) || is_background(kind));
}
