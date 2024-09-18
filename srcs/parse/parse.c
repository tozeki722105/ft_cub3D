/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:36:49 by toshi             #+#    #+#             */
/*   Updated: 2024/09/18 18:07:34 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_loader	init_loader(void)
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

static void	fill_space_to_wall(char **map_data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			if (map_data[y][x] == ' ')
				map_data[y][x] = '1';
			x++;
		}
		y++;
	}
}

static double	convert_player_angle(char **map_data, t_pos grid_pos)
{
	if (map_data[(int)grid_pos.y][(int)grid_pos.x] == 'N')
		return (90);
	else if (map_data[(int)grid_pos.y][(int)grid_pos.x] == 'S')
		return (270);
	else if (map_data[(int)grid_pos.y][(int)grid_pos.x] == 'W')
		return (180);
	else
		return (0);
}

static t_pos	convert_player_pos(t_pos grid_pos)
{
	t_pos	pos;

	pos.x = (grid_pos.x * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	pos.y = (grid_pos.y * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	return (pos);
}

t_loader	parse(char *path)
{
	t_loader	loader;
	int			fd;

	if (!ft_validate_extention(path, ".cub"))
		ft_my_perror_exit("The file extension is different", 1);
	fd = open(path, O_RDONLY);
	if (fd == SYSERR)
		ft_perror_exit(NULL, 1);
	loader = init_loader();
	load_textures(fd, &loader);
	load_map_str_to_list(fd, &loader);
	close(fd);
	trim_map_list(&(loader.map_head), "");
	load_map_list_to_data(loader.map_head, &loader);
	if (!validate_map_data(loader.map_data))
		ft_my_perror_exit("The map is not surrounded by walls", 1);
	fill_space_to_wall(loader.map_data);
	if (!validate_grid_pos(loader.map_data, &(loader.player_grid_pos)))
		ft_my_perror_exit("Put only one player element in the map", 1);
	loader.player_pos = convert_player_pos(loader.player_grid_pos);
	loader.player_angle = convert_player_angle(loader.map_data,
			loader.player_grid_pos);
	return (loader);
}

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q cub3d");
// }
// int main(int argc, char **argv)
// {
// 	t_loader loader;
// 	if (argc != 2)
// 		return (1);
// 	loader = parse(argv[1]);
// 	print_texture(loader);
// 	print_map_player(loader);
// 	free_loader(loader);
// }
