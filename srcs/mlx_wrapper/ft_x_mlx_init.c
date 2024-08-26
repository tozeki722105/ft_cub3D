/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_mlx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:36:05 by tyamauch          #+#    #+#             */
/*   Updated: 2024/08/26 14:35:07 by toshi            ###   ########.fr       */
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
		ft_my_perror_exit("mlx_init error", 1);
	return (ret);
}
