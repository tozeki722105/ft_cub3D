/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_can_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:26:52 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:02:16 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_can_open(char *path, int open_mode)
{
	int	fd;

	fd = open(path, open_mode);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}
