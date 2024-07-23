
#include "parse.h"

void add_textures(t_loader *loader, char *str)
{
	if (!is_member_default(*loader, loader->kind))
		my_perror_exit("Duplicate elements", 0);
	else if (is_wall(loader->kind))
		add_wall(loader, loader->kind, str);
	else if (is_view_background(loader->kind))
		add_color(loader, loader->kind, str);
}

void	load_textures(int fd, t_loader *loader)
{
	char		*str;

	while (!is_textures_full(*loader))
	{
		str = get_next_line(fd);
		if (!str)
			my_perror_exit("error1", 0);
		loader->kind = parse_kind(str);
		if (loader->kind == KIND_MAP)
			my_perror_exit("error1", 0);
		else if (loader->kind == KIND_FALSE)
			my_perror_exit("Contains invalid elements", 0);
		add_textures(loader, str);
		free(str);
	}
}

void	load_map_list(int fd, t_loader *loader)
{
	char		*str;
	t_map_node	*new;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		loader->kind = parse_kind(str);
		if (loader->kind == KIND_FALSE)
			my_perror_exit("error3", 0);
		if (is_texture(loader->kind))
			my_perror_exit("error4", 0);
		char *val = ft_strtrim_sepasets(str, "\n", " \n");
		new = make_new_map_node(val);
		add_last_map_node(&(loader->map_head), new);
		free(str);
	}	
}