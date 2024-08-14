/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:39:01 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/13 14:39:03 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_map_node(t_map_node *map_node)
{
	free(map_node->val);
	free(map_node);
}

void	free_map_list(t_map_node *ptr)
{
	t_map_node	*next_ptr;

	if (!ptr)
		return ;
	next_ptr = ptr->next;
	while (next_ptr)
	{
		free_map_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_map_node(ptr);
}

void	free_loader(t_loader loader)
{
	free(loader.north_path);
	free(loader.south_path);
	free(loader.west_path);
	free(loader.east_path);
	free_map_list(loader.map_head);
	ft_free_double_str(loader.map_data);
}
