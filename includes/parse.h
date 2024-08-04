#ifndef PARSE_H
# define PARSE_H

// # include "ogv1.h"
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "config.h"
#include "../library/libft/libft.h"
#include "../library/gnl/get_next_line.h"

enum e_dir
{
	FRONT = 1,
	BACK = -1
} ;

typedef	enum e_line_kind
{
	KIND_NORTH,
	KIND_SOUTH,
	KIND_WEST,
	KIND_EAST,
	KIND_FLOOR,
	KIND_CEILING,
	KIND_NEWLINE,
	KIND_MAP,
	KIND_FALSE
}	t_line_kind;

typedef struct s_map_node
{
	char *val;
	struct s_map_node *next;
}	t_map_node;

typedef struct 
{
	t_line_kind kind;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	t_map_node	*map_head;
	char		**map_data;
	t_pos		player_grid_pos;
	t_pos		player_pos;
	double		player_angle;
	int 		map_y_count;
	int 		map_x_count;
}	t_loader;

t_loader	parse(char *path);

//load_map_list_to_data.c
void load_map_list_to_data(t_map_node *ptr, t_loader *loader);

// load_map_str_to_list.c
void	load_map_str_to_list(int fd, t_loader *loader);

//load_textures.c
void	load_textures(int fd, t_loader *loader);

//trim_map_list.c
void	trim_map_list(t_map_node **head, char *trimed_node_val);

// utils_bool.c
bool	is_player(char c);
bool	is_map_element(char c);
bool	is_wall(t_line_kind kind);
bool	is_background(t_line_kind kind);
bool	is_texture(t_line_kind kind);

// utils_free.c
void	free_map_list(t_map_node *ptr);
void	free_loader(t_loader loader);

// utils_load.c
t_line_kind	get_line_kind(char *str);
char *extract_val(char *str, t_line_kind kind);

// utils_print.c
void	print_map_list(t_map_node *ptr);
void	print_texture(t_loader loader);
void	print_map_player(t_loader loader);

// validate_map_data.c
bool	validate_map_data(char **map_data);

//utils_libft.c
size_t	ft_count_rows(char **d_str);
char	**ft_double_str_dup(char **d_str);
void	ft_free_double_str(char **d_str);
bool	ft_isequal(char *s1, char *s2);
void	ft_perror_exit(char *err_s, int exit_code);
bool	ft_perror_ret_false(char *err_s);
bool	ft_validate_extention(char *path, char *extention);
bool	ft_can_open(char *path, int open_mode);
char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set, const char *back_trim_set);

#endif