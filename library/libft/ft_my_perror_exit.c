/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_perror_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:24:59 by toshi             #+#    #+#             */
/*   Updated: 2024/08/08 00:25:00 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_my_perror_exit(char *err_s, int exit_code)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	exit(exit_code);
}