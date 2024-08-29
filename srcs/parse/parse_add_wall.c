/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 03:52:34 by toshi             #+#    #+#             */
/*   Updated: 2024/08/29 03:52:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_wall(t_loader *loader, t_line_kind kind, char *str)
{
	char	*val;

	val = extract_val(str, kind);
	if (!ft_can_open(val, O_RDONLY))
		ft_my_perror_exit("The texture path is incorrect", 1);
	if (kind == KIND_NORTH)
		loader->north_path = val;
	else if (kind == KIND_SOUTH)
		loader->south_path = val;
	else if (kind == KIND_WEST)
		loader->west_path = val;
	else if (kind == KIND_EAST)
		loader->east_path = val;
}