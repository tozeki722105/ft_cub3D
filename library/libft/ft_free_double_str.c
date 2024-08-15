/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:27:13 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 19:57:55 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_str(char **d_str)
{
	size_t	i;

	i = 0;
	if (!d_str)
		return ;
	while (d_str[i])
		free(d_str[i++]);
	free(d_str);
}
