/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_load_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:33:34 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/29 04:01:12 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
	if (kind == KIND_NEWLINE)
		return (true);
	else
		return (false);
}

static bool	is_textures_full(t_loader loader)
{
	return (loader.north_path && loader.south_path && loader.west_path
		&& loader.east_path && loader.floor_color > -1
		&& loader.ceiling_color > -1);
}

static void	add_textures(t_loader *loader, char *str)
{
	if (!is_member_default(*loader, loader->kind))
		ft_my_perror_exit("Duplicate elements", 1);
	else if (is_wall(loader->kind))
		add_wall(loader, loader->kind, str);
	else if (is_background(loader->kind))
		add_color(loader, loader->kind, str);
}

void	load_textures(int fd, t_loader *loader)
{
	char	*str;

	while (!is_textures_full(*loader))
	{
		str = get_next_line(fd);
		if (!str)
			ft_my_perror_exit("There is missing information before map_data",
				1);
		loader->kind = get_line_kind(str);
		if (loader->kind == KIND_MAP)
			ft_my_perror_exit("There is missing information before map_data",
				1);
		else if (loader->kind == KIND_FALSE)
			ft_my_perror_exit("Contains invalid elements", 1);
		add_textures(loader, str);
		free(str);
	}
}
