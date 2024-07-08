/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:24:58 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/22 19:08:39 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	cn;

	cn = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		cn = (unsigned int)(n * -1);
	}
	if (cn >= 10)
		ft_putnbr_fd(cn / 10, fd);
	ft_putchar_fd('0' + cn % 10, fd);
}

//int main(void)
//{
//	int n = INT_MIN;
//	printf("%d\n", n);
//	int nn = (unsigned int) n;
//	printf("%d\n", nn);
//	int nnn = (int) nn;
//	printf("%d", nnn);
//	ft_putnbr_fd(n, 1);
//}