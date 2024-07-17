/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itonbase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:53:30 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/25 21:31:08 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

char	*itonbase(int num, unsigned int base);
size_t	get_dig_nbase(unsigned int num, unsigned int base);
char *set_string_nbase(unsigned int num, unsigned int base, size_t dig, int negative);

void	*ft_calloc(size_t count, size_t size);
void	*ft_bzero(void *buf, size_t n);
void	*ft_memset(void *buf, int ch, size_t n);

int main (void)
{
	int n = -96552;
	int base = 16;
	printf("\n%s\n", itonbase(n, base));
	return (1);
}

char *itonbase(int num, unsigned int base)
{
	unsigned int	cnum;
	int				negative;
	size_t			dig;

	if (base > 16)
		return (NULL);
	cnum = (unsigned int)num;
	if (num < 0 && base == 10)
		cnum = (unsigned int)(num * -1);
	negative = (num < 0 && base == 10);
	dig = (num < 0 && base == 10);
	dig += get_dig_nbase(cnum, base);
	return (set_string_nbase(cnum, base, dig, negative));
}

char *set_string_nbase(unsigned int num, unsigned int base, size_t dig, int negative)
{
	const char	*string_base = "0123456789ABCDEF";
	char		*str;

	str = (char *)ft_calloc((dig + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (dig > 0)
	{
		str[--dig] = string_base[num % base];
		num /= base;
	}
	if (negative != 0)
		str[0] = '-';
	return (str);
}

size_t	get_dig_nbase(unsigned int num, unsigned int base)
{
	size_t	dig;
	
	dig = 1;
	while (num >= base)
	{
		num /= base;
		dig++;
	}
	return (dig);
}

//void	*ft_calloc(size_t count, size_t size)
//{
//	void	*str;

//	if (size == 0 || count == 0)
//		ft_calloc(1, 1);
//	else if (size > SIZE_MAX / count)
//		return (NULL);
//	str = (void *)malloc(size * count);
//	if (str == NULL)
//		return (NULL);
//	ft_bzero(str, size * count);
//	return (str);
//}

//void	*ft_bzero(void *buf, size_t n)
//{
//	return (ft_memset(buf, '\0', n));
//}

//void	*ft_memset(void *buf, int ch, size_t n)
//{
//	unsigned char	*cbuf;
//	unsigned char	cch;
//	size_t			i;

//	cbuf = (unsigned char *)buf;
//	cch = (unsigned char)ch;
//	i = 0;
//	while (i < n)
//	{
//		cbuf[i] = cch;
//		i++;
//	}
//	return (buf);
//}
