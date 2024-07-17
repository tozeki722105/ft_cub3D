#ifndef PARSE_H
# define PARSE_H

# include "ogv1.h"

typedef	enum e_parse_kind
{
	KIND_MAP,
	WALL,
	KIND_NORTH,
	KIND_SOUTH,
	KIND_WEST,
	KIND_EAST,
	FLOOR_CEILING,
	KIND_FLOOR,
	KIND_CEILING,
	KIND_NEWLINE,
	KIND_FALSE,
}	t_parse_kind;

typedef struct s_map_node
{
	char *val;
	struct s_map_node *next;
}	t_mnode;

typedef struct 
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	char	**map_data;
	int		player_x;
	int		player_y;
}	t_reader;

#endif