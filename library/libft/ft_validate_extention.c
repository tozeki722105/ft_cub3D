/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_extention.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:18 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:06:12 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @param path not NULL
/// @param extention not NULL (.)start
bool	ft_validate_extention(char *path, char *extention)
{
	char	*ptr;

	ptr = ft_strrchr(path, *extention);
	if (!ptr || ptr == path)
		return (false);
	return (ft_isequal(ptr, extention));
}
