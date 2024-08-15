/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_perror_ret_false.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:25:04 by toshi             #+#    #+#             */
/*   Updated: 2024/08/15 20:04:13 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_my_perror_ret_false(char *err_s)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	return (false);
}
