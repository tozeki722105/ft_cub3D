#ifndef PARSE_H
# define PARSE_H

// # include "ogv1.h"
#include "utils.h"

typedef struct s_pos
{
	int	x;
	int y;
} t_pos;

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
	t_parse_kind	kind;
	t_parse_kind	prev_kind;
	t_load_mode		mode;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	t_map_node	*map_head;
	char		**map_data;
	t_pos		player_pos;
}	t_loader;

void	my_perror_exit(char *err_s, int exit_code);
bool	validate_extention(char *path, char *extention);
bool	ft_isequal(char *s1, char *s2);
bool	is_player(char c);
bool	is_map_element(char c);
bool	is_filled_map_element(char c);
void	free_map_node(t_map_node *map_node);
void	free_map_node_list(t_map_node *ptr);
void	free_reader(t_reader reader);
t_map_node *make_new_map_node(char *str);
t_map_node *find_last_map_node(t_map_node *ptr);
void add_last_map_node(t_map_node **head, t_map_node *new);
t_reader init_reader();
t_loader init_loader();
void	print_texture(t_reader reader);
void	print_map(char **map_data);
size_t ft_count_rows(char **d_str);

bool	is_map_str(char *str);
t_parse_kind	parse_kind(char *str);
bool	is_member_default(t_loader loader, t_parse_kind kind);
bool	is_textures_full(t_loader loader);
bool	is_wall(t_parse_kind kind);
bool	is_view_background(t_parse_kind kind);
bool	is_texture(t_parse_kind kind);
int make_rgb_color(int r, int g, int b);
char *extract_val(char *str, t_parse_kind kind);
int convert_rgb_color(char *color_str);
void	add_wall(t_loader *loader, t_parse_kind kind, char *str);
void	add_color(t_loader *loader, t_parse_kind kind, char *str);
void	print_map_node(t_map_node *ptr);
void	trim_map_list(t_map_node **head, char *trimed_node_val);
bool	is_contained_newline(t_map_node *ptr);
char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set, const char *back_trim_set);

bool	validate_map_data(char **map_data);

void	load_map_list(int fd, t_loader *loader);
void	load_textures(int fd, t_loader *loader);
#endif