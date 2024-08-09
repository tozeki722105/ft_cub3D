#include "parse.h"

void	add_color(t_loader *loader, t_line_kind kind, char *str);

static void	add_wall(t_loader *loader, t_line_kind kind, char *str)
{
	char *val;

	val = extract_val(str, kind);
	if (!ft_can_open(val, O_RDONLY))
		ft_my_perror_exit("The texture path is incorrect", 0);
	if (kind == KIND_NORTH)
		loader->north_path = val;
	else if (kind == KIND_SOUTH)
		loader->south_path = val;
	else if (kind == KIND_WEST)
		loader->west_path = val;
	else if (kind == KIND_EAST)
		loader->east_path = val;
}

static bool	is_member_default(t_loader loader, t_line_kind kind)
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

static bool	is_textures_full(t_loader loader)
{
	return (loader.north_path && loader.south_path
		&& loader.west_path && loader.east_path
		&& loader.floor_color > -1 && loader.ceiling_color > -1);
}

static void add_textures(t_loader *loader, char *str)
{
	if (!is_member_default(*loader, loader->kind))
		ft_my_perror_exit("Duplicate elements", 0);
	else if (is_wall(loader->kind))
		add_wall(loader, loader->kind, str);
	else if (is_background(loader->kind))
		add_color(loader, loader->kind, str);
}

void	load_textures(int fd, t_loader *loader)
{
	char		*str;

	while (!is_textures_full(*loader))
	{
		str = get_next_line(fd);
		if (!str)
			ft_my_perror_exit("There is missing information before map_data", 0);
		loader->kind = get_line_kind(str);
		if (loader->kind == KIND_MAP)
			ft_my_perror_exit("There is missing information before map_data", 0);
		else if (loader->kind == KIND_FALSE)
			ft_my_perror_exit("Contains invalid elements", 0);
		add_textures(loader, str);
		free(str);
	}
}