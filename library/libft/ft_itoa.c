/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:34:53 by tozeki            #+#    #+#             */
/*   Updated: 2024/02/15 08:51:37 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static size_t	get_dig(unsigned int n)
{
	size_t	dig;

	dig = 1;
	while (n >= 10)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

static char	*set_return_str(unsigned int n, size_t dig, int sign)
{
	char	*str;

	str = (char *)ft_calloc(dig + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (dig > 0)
	{
		str[--dig] = (char)((n % 10) + '0');
		n /= 10;
	}
	if (sign < 0)
		str[dig] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	cn;
	size_t			dig;
	int				sign;

	cn = (unsigned int)n;
	dig = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		cn = (unsigned int)(n * -1);
		dig++;
	}
	dig += get_dig(cn);
	return (set_return_str(cn, dig, sign));
}

//int main (void)
//{
//	int n = INT_MIN + 1;
//	printf("%s", ft_itoa(n));
//	return (1);
//}