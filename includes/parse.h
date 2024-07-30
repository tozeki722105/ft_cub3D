#ifndef PARSE_H
# define PARSE_H

// # include "ogv1.h"
#include "utils.h"

typedef struct s_pos
{
	double	x;
	double y;
} t_pos;

typedef struct s_player
{
	t_pos	pos;
	double	angle;
} t_player;


enum e_dir
{
	FRONT,
	BACK,
} ;

typedef enum e_load_mode
{
	DEFAULT,
	MAP_MODE,
}	t_load_mode;

typedef	enum e_parse_kind
{
	KIND_DEFAULT,
	KIND_NORTH,
	KIND_SOUTH,
	KIND_WEST,
	KIND_EAST,
	KIND_FLOOR,
	KIND_CEILING,
	KIND_NEWLINE,
	KIND_MAP,
	KIND_FALSE,
}	t_parse_kind;

typedef struct s_map_node
{
	char *val;
	struct s_map_node *next;
}	t_map_node;

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

typedef struct 
{
	t_parse_kind kind;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	t_map_node	*map_head;
	char		**map_data;
	t_pos		player_pos;
	double		player_angle;
}	t_loader;

// parse_utils_bool.c
bool	is_player(char c);
bool	is_map_element(char c);
bool	is_filled_map_element(char c);
bool	is_wall(t_parse_kind kind);
bool	is_background(t_parse_kind kind);

// parse_utils_bool2.c
bool	is_texture(t_parse_kind kind);
bool	is_map_str(char *str);
bool	is_member_default(t_loader loader, t_parse_kind kind);
bool	is_textures_full(t_loader loader);

//parse_utils_map_node.c
t_map_node *make_new_map_node(char *str);
t_map_node *find_last_map_node(t_map_node *ptr);
void add_last_map_node(t_map_node **head, t_map_node *new);
void	free_map_node_list(t_map_node *ptr);

//parse_utils_map_node2.c
void	print_map_node(t_map_node *ptr);
void	trim_map_list(t_map_node **head, char *trimed_node_val);

//parse_utils.c
t_loader init_loader();
void	free_loader(t_loader loader);
void	print_texture(t_loader loader);
void	print_map(char **map_data);
void	print_player(t_loader loader);

//parse_load_utils.c
t_parse_kind	parse_kind(char *str);
char *extract_val(char *str, t_parse_kind kind);
void	add_wall(t_loader *loader, t_parse_kind kind, char *str);

//parse_load_utils2.c
void	add_color(t_loader *loader, t_parse_kind kind, char *str);

//parse_load_utils3.c
char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set, const char *back_trim_set);

//parse_utils_libft.c
size_t ft_count_rows(char **d_str);
char **ft_double_str_dup(char **d_str);
void	ft_free_double_str(char **d_str);
bool	ft_isequal(char *s1, char *s2);
void	ft_perror_exit(char *err_s, int exit_code);
bool	ft_perror_ret_false(char *err_s);

// parse_load.c
void	load_map_list(int fd, t_loader *loader);
void	load_textures(int fd, t_loader *loader);

//parse_validate_map_data.c
bool	validate_map_data(char **map_data);

//parse_validate_map_data_utils.c
bool	validate_surrounded_wall_and_fill_space(char **map_data);

#endif