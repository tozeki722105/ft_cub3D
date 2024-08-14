/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_load_map_str_to_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:32:11 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/13 14:32:16 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_map_node	*make_new_map_node(char *str)
{
	t_map_node	*new;

	new = (t_map_node *)ft_x_malloc(sizeof(t_map_node));
	new->val = str;
	new->next = NULL;
	return (new);
}

static t_map_node	*find_last_map_node(t_map_node *ptr)
{
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void	add_last_map_list(t_map_node **head, t_map_node *new)
{
	if (!(*head))
	{
		*head = new;
		return ;
	}
	find_last_map_node(*head)->next = new;
}

static void	add_map_head(t_loader *loader, char *str)
{
	t_map_node	*new;
	char		*val;

	val = ft_x_strtrim_sepasets(str, "\n", " \n");
	new = make_new_map_node(val);
	add_last_map_list(&(loader->map_head), new);
}

void	load_map_str_to_list(int fd, t_loader *loader)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		loader->kind = get_line_kind(str);
		if (loader->kind == KIND_FALSE)
			ft_my_perror_exit("Contains invalid elements", 0);
		if (is_texture(loader->kind))
			ft_my_perror_exit("Duplicate elements", 0);
		add_map_head(loader, str);
		free(str);
	}
}
