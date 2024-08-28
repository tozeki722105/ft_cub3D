/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extract_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 03:54:33 by toshi             #+#    #+#             */
/*   Updated: 2024/08/29 03:54:55 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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