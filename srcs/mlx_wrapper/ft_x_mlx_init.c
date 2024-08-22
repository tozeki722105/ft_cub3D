/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:36:05 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/19 16:36:20 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "utils.h"

void	*ft_x_mlx_init(void)
{
	void	*ret;

	ret = mlx_init();
	if (ret == NULL)
		ft_my_perror_exit("mlx_init", 1);
	return (ret);
}
