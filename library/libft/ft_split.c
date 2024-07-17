/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:23:20 by tozeki            #+#    #+#             */
/*   Updated: 2023/03/21 22:07:57 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len_i(const char *s, char c)
{
	size_t	len_i;
	size_t	i;

	len_i = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			len_i++;
		i++;
	}
	return (len_i);
}

static char	**free_all(char **strs)
{
	size_t	i_strs;

	i_strs = 0;
	while (strs[i_strs] != NULL)
	{
		free (strs[i_strs]);
		i_strs++;
	}
	free (strs);
	return (NULL);
}

static char	**insert_strs(const char *s, char c, char **strs)
{
	size_t	i;
	size_t	i_strs;
	size_t	len_j;

	i = 0;
	i_strs = 0;
	len_j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			strs[i_strs] = ft_substr(&s[i - len_j], 0, len_j + 1);
			if (strs[i_strs] == NULL)
				return (free_all (strs));
			i_strs++;
			len_j = 0;
		}
		else if (s[i] != c)
			len_j++;
		i++;
	}
	strs[i_strs] = NULL;
	return (strs);
}

char	**ft_split(const char *s, char c)
{
	size_t	len_i;
	char	**strs;

	if (s == NULL)
		return (NULL);
	len_i = get_len_i(s, c);
	strs = (char **)ft_calloc(len_i + 1, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	return (insert_strs(s, c, strs));
}

//int main(void)
//{
//	char s[] = "  tripouille  42  ";
//	char c = ' ';

//	system("leaks -q a.out");
//	ft_split(s,c);
//	//split(s,c);
//}