/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:39:58 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/15 18:45:25 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size == 0 || count == 0)
		return (ft_calloc(1, 1));
	else if (size > SIZE_MAX / count)
		return (NULL);
	str = (void *)malloc(size * count);
	if (str == NULL)
		return (NULL);
	return (ft_bzero(str, size * count));
}

//int main(void)
//{
//	int *ptr,*p;
//	int i;
//	int n = 0;

//	/* 500個のintサイズのメモリを確保 */
//	ptr = (int *)calloc(n,4);
//	if(ptr == NULL) {
//		printf("メモリが確保できません\n");
//		exit(EXIT_FAILURE);
//	}

//	p = ptr;
//	for (i=0; i<n; i++) {
//		*p = i;
//		printf("%d ",*p);
//		p++;
//	}

//	/* メモリの開放 */
//	free(ptr);

//	return 0;
//}