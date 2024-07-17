/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:46:51 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/25 16:44:53 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>

static size_t	get_start_set_sign(const char *str, int *psign)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		*psign = -1;
		i++;
	}
	return (i);
}

static size_t	get_end(const char *str, size_t i)
{
	while (str[i] != '\0' && ft_isdigit(str[i]) != 0)
		i++;
	return (i);
}

static long	num_check(long num, const char c, int sign)
{
	if (sign > 0)
	{
		if (num > (LONG_MAX / 10))
			return (LONG_MAX);
		else if (num == (LONG_MAX / 10) && (c - '0') > (LONG_MAX % 10))
			return (LONG_MAX);
	}
	else if (sign < 0)
	{
		if (num < (LONG_MIN / 10))
			return (LONG_MIN);
		else if (num == (LONG_MIN / 10) && (c - '0') > -(LONG_MIN % 10))
			return (LONG_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	size_t	start;
	size_t	end;
	long	overflow;

	num = 0;
	sign = 1;
	start = get_start_set_sign(str, &sign);
	end = get_end(str, start);
	while (start < end)
	{	
		overflow = num_check(num, str[start], sign);
		if (overflow != 0)
			return ((int)overflow);
		num = (num * 10) + (sign * (str[start] - '0'));
		start++;
	}
	return ((int)(num));
}

//int main(void)
//{
//	char str[] = "9223372036854775809";	
//	printf("\n%d", ft_atoi(str));
//	printf("\n本物%d", atoi(str));
//	return (1);
//}