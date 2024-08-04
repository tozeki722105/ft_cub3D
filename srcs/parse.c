/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:36:49 by toshi             #+#    #+#             */
/*   Updated: 2024/08/05 04:39:33 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_loader init_loader();

bool	is_contained_newline(t_map_node *ptr)
{
	while (ptr && !ft_isequal(ptr->val, ""))
		ptr = ptr->next;
	if (ptr)
		return (true);
	return (false);
}

static bool	validate_grid_pos(char **map_data, t_pos *grid_pos)
{
	t_pos cur;

	cur.y = 0;
	while (map_data[(int)cur.y])
	{
		cur.x = 0;
		while (map_data[(int)cur.y][(int)cur.x])
		{
			if (is_player(map_data[(int)cur.y][(int)cur.x]))
			{
				if (grid_pos->x == -1 && grid_pos->y == -1)
					*grid_pos = cur;
				else
					return (false);
			}
			cur.x++;
		}
		cur.y++;
	}
	if (grid_pos->x == -1 || grid_pos->y == -1)
		return (false);
	return (true);
}

static double convert_player_angle(char **map_data, t_pos grid_pos)
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

static t_pos convert_player_pos(t_pos grid_pos)
{
	t_pos pos;

	pos.x = (grid_pos.x * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	pos.y = (grid_pos.y * MAP_PANEL_SIDE) + (MAP_PANEL_SIDE / 2);
	return (pos);
}

t_loader	parse(char *path)
{
	t_loader	loader;
	int			fd;

	if (!ft_validate_extention(path, ".cub"))
		ft_perror_exit("The file extension is different", 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_perror_exit("A system call failed", 0);
	loader = init_loader();
	load_textures(fd, &loader);
	load_map_str_to_list(fd, &loader);
	close(fd);
	trim_map_list(&(loader.map_head), "");
	if (is_contained_newline(loader.map_head))
		ft_perror_exit("Only one map_data is allowed", 0);
	load_map_list_to_data(loader.map_head, &loader);
	if (!validate_map_data(loader.map_data))
		exit(0);
	if (!validate_grid_pos(loader.map_data, &(loader.player_grid_pos)))
		ft_perror_exit("Put only one player element in the map", 0);
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
// 	print_player(loader);
// 	print_map_player(loader);
// 	free_loader(loader);
// }