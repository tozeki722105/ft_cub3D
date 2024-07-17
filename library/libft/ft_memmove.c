/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:59:47 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/19 15:34:59 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	if (dest > src)
	{
		while (n > 0)
		{
			cdest[n - 1] = csrc[n - 1];
			n--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}

//int main(void)
//{
//	char dest[] = "0123456789";
//	char src[] = "dfghjklfghjk";

//	//printf("%s\n", dest);
//	//ft_memmove(&dest[0], &dest[5], 6);
//	//printf("%s\n", dest);

//	printf("%s\n", (char *)memmove(dest, NULL, 0));
//	printf("%s\n", (char *)ft_memmove(dest, NULL, 0));

//	return (0);
//}