/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:36:36 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/28 22:08:14 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/// @brief sapace_only_str is true 
static bool	is_map_str(char *str)
{
	bool	player_flag;

	player_flag = false;
	if (*str == '\n')
		return (false);
	while (*str && *str != '\n')
	{
		if (!is_map_element(*str)
			|| player_flag && is_player(*str))
			return (false);
		if (is_player(*str))
			player_flag = true;
		str++;
	}
	return (true);
}

t_line_kind	get_line_kind(char *str)
{
	if (*str == '\n')
		return (KIND_NEWLINE);
	if (is_map_str(str))
		return (KIND_MAP);
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (KIND_NORTH);
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (KIND_SOUTH);
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (KIND_WEST);
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (KIND_EAST);
	if (ft_strncmp(str, "F ", 2) == 0)
		return (KIND_FLOOR);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (KIND_CEILING);
	return (KIND_FALSE);
}

char	*extract_val(char *str, t_line_kind kind)
{
	size_t	identifer_len;
	char	*val_include_space;
	char	*val;

	if (is_wall(kind))
		identifer_len = 2;
	else
		identifer_len = 1;
	val_include_space = ft_x_substr(str, identifer_len,
			ft_strlen(str) - identifer_len);
	val = ft_x_strtrim(val_include_space, " \t\n");
	free(val_include_space);
	return (val);
}
