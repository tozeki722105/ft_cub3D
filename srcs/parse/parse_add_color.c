/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:30:58 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/13 14:30:59 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	validate_color_str(char *str)
{
	char	*prev;
	size_t	comma_count;

	prev = NULL;
	comma_count = 0;
	while (*str)
	{
		if (!(ft_isdigit(*str) || *str == ','))
			return (ft_my_perror_ret_false("Invalid character in F or C"));
		if (*str == ',' && (!prev || *prev == ','))
			return (ft_my_perror_ret_false("Consecutive commas"));
		if (*str == ',')
			comma_count++;
		prev = str;
		str++;
	}
	if (comma_count != 2)
		return (ft_my_perror_ret_false(
				"The number of rgb elements is not appropriate"));
	return (true);
}

static int	*make_rgb_array(char *str)
{
	int		*rgb_array;
	int		i;
	char	*sep_ptr;
	char	*sub_s;

	rgb_array = (int *)ft_x_malloc(sizeof(int) * 3);
	i = 0;
	while (i < 3)
	{
		sep_ptr = ft_strchr(str, ',');
		if (!sep_ptr)
			sep_ptr = ft_strchr(str, '\0');
		sub_s = ft_x_substr(str, 0, (size_t)(sep_ptr - str));
		rgb_array[i++] = ft_atoi(sub_s);
		free(sub_s);
		str = sep_ptr + sizeof(char);
	}
	return (rgb_array);
}

static int	convert_rgb_color(int r, int g, int b)
{
	int	res;

	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	res = r;
	res <<= 8;
	res += g;
	res <<= 8;
	res += b;
	return (res);
}

void	add_color(t_loader *loader, t_line_kind kind, char *str)
{
	char	*val;
	int		color;
	int		*rgb_array;

	val = extract_val(str, kind);
	if (!validate_color_str(val))
		exit(0);
	rgb_array = make_rgb_array(val);
	free(val);
	color = convert_rgb_color(rgb_array[0], rgb_array[1], rgb_array[2]);
	if (color == -1)
		ft_my_perror_exit("RGB contains value other than 0 to 255", 0);
	free(rgb_array);
	if (kind == KIND_FLOOR)
		loader->floor_color = color;
	else if (kind == KIND_CEILING)
		loader->ceiling_color = color;
}
