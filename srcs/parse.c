/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:36:49 by toshi             #+#    #+#             */
/*   Updated: 2024/08/02 13:59:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static size_t count_map_size(t_map_node *ptr, size_t *map_y_count)
{
	size_t map_x_count;
	size_t ptr_len;
	
	map_x_count = 0;
	*map_y_count = 0;
	while (ptr)
	{
		ptr_len = ft_strlen(ptr->val);
		if (map_x_count < ptr_len)
			map_x_count = ptr_len;
		ptr = ptr->next;
		(*map_y_count)++;
	}
	return (map_x_count);
}

static char **convert_map_data(t_map_node *ptr, t_loader *loader)
{
	size_t	map_x_count;
	size_t	map_y_count;
	char **map;
	size_t i;

	map_x_count = count_map_size(ptr, &map_y_count);
	map = (char **)malloc(sizeof(char *) * (map_y_count + 1));
	i = 0;
	while (i < map_y_count)
	{
		map[i] = (char *)malloc(sizeof(char) * (map_x_count + 1));
		ft_memset(map[i], ' ', map_x_count);
		ft_memmove(map[i], ptr->val, ft_strlen(ptr->val));
		map[i][map_x_count] = '\0';
		i++;
		ptr = ptr->next;
	}
	map[i] = NULL;
	loader->map_y_count = map_y_count;
	loader->map_x_count = map_x_count;
	return (map);
}


static bool	validate_player_pos(char **map_data, t_pos *player_pos)
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
				if (player_pos->x == -1 && player_pos->y == -1)
					*player_pos = cur;
				else
					return (false);
			}
			cur.x++;
		}
		cur.y++;
	}
	if (player_pos->x == -1 || player_pos->y == -1)
		return (false);
	return (true);
}

static double get_player_angle(char **map_data, t_pos pos)
{
	if (map_data[(int)pos.y][(int)pos.x] == 'N')
		return (90);
	else if (map_data[(int)pos.y][(int)pos.x] == 'S')
		return (270);
	else if (map_data[(int)pos.y][(int)pos.x] == 'W')
		return (180);
	else
		return (0);
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
	load_map_list(fd, &loader);
	close(fd);
	trim_map_list(&(loader.map_head), "");
	if (is_contained_newline(loader.map_head))
		ft_perror_exit("Only one map_data is allowed", 0);
	loader.map_data = convert_map_data(loader.map_head, &loader);
	if (!validate_map_data(loader.map_data))
		exit(0);
	if (!validate_player_pos(loader.map_data, &(loader.player_pos)))
		ft_perror_exit("Put only one player element in the map", 0);
	loader.player_angle = get_player_angle(loader.map_data, loader.player_pos);
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
// 	print_map(loader);
// 	free_loader(loader);
// }


// bool is_valid_data(char *str, char **dest)
// {
// 	char *cpy = (char *)malloc(sizeof(char) * strlen(str));
// 	size_t i = 0;
// 	while (str)
// 	{
// 		if (!isdigit(*str))
// 			return (false);
// 		else
// 			cpy[i++] = *str;
// 		str++;
// 	}
// 	*dest = cpy;
// 	return (true);
// }

// int main(int argc, char **argv)
// {
// 	char *dest;

// 	if (!is_valid_data(argv[1], &dest))
// 		exit (1);
// 	printf("%s\n", dest);
// }