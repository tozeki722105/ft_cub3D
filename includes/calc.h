/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:42:55 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/29 02:34:26 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "../library/libft/libft.h"
# include "draw.h"
# include "main.h"
# include "config.h"
# include <math.h>

enum			e_axis
{
	VERTICAL,
	HORIZONTAL,
};

typedef struct s_inter
{
	t_pos		pos;
	double		distance;
	enum e_axis	axis;
	double		angle;
	double		origin_offset;
	double		wall_height;
}				t_inter;

//calc_interseciton.c
t_inter			calc_intersection(t_mlx *mlx, double ray_angle);

//calc_utils.c
double			sin_wrap(double angle);
double			cos_wrap(double angle);
double			tan_wrap(double angle);
double			cot_wrap(double angle);

//calc_utils2.c
double			fix_angle(double angle);
t_pos			fix_move(t_mlx *mlx, t_pos pos, double move_angle, int step);
bool			is_up(double degree);
bool			is_right(double degree);

#endif
