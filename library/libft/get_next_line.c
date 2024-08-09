/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:35:01 by tozeki            #+#    #+#             */
/*   Updated: 2024/08/07 23:36:38 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t count, size_t size);
char	*free_str_set_null(char *str);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcat(char *dest, const char *src, size_t size);

static char	*append_str(char *dest, char *src, ssize_t count)
{
	size_t	len;
	char	*buf;

	if (count == 0 && *dest == '\0')
		return (free_str_set_null(dest));
	len = 1 + gnl_strlen(dest) + count;
	buf = (char *)gnl_calloc(len, sizeof(char));
	if (buf == NULL)
		return (free_str_set_null(dest));
	gnl_strlcat(buf, dest, len);
	gnl_strlcat(buf, src, len);
	free(dest);
	return (buf);
}

static char	*get_save(int fd, char *save)
{
	char		*buffer;
	ssize_t		count;

	buffer = (char *)gnl_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (free_str_set_null(save));
	while (gnl_strchr(buffer, '\n') == NULL)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free (buffer);
			return (free_str_set_null(save));
		}
		save = append_str(save, buffer, count);
		if (save == NULL)
			return (free_str_set_null(buffer));
		if (count == 0)
			break ;
	}
	free(buffer);
	return (save);
}

static char	*get_currentline(char *save)
{
	char	*ad_endl;
	size_t	len;
	char	*buf;

	ad_endl = gnl_strchr(save, '\n');
	if (ad_endl == NULL)
		ad_endl = gnl_strchr(save, '\0');
	else
		ad_endl++;
	len = (size_t)((ad_endl - save) + 1);
	buf = (char *)gnl_calloc(len, sizeof(char));
	if (buf == NULL)
		return (NULL);
	gnl_strlcat(buf, save, len);
	return (buf);
}

static char	*set_nextline(char *save)
{
	char	*ad_startl;
	size_t	len;
	char	*buf;

	ad_startl = gnl_strchr(save, '\n');
	if (ad_startl == NULL)
		ad_startl = gnl_strchr(save, '\0') - 1;
	len = (size_t)(gnl_strchr(save, '\0') - ad_startl);
	buf = (char *)gnl_calloc(len, sizeof(char));
	if (buf == NULL)
		return (free_str_set_null(save));
	gnl_strlcat(buf, ad_startl + 1, len);
	free(save);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*currentline;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (save == NULL)
	{
		save = (char *)gnl_calloc(1, sizeof(char));
		if (save == NULL)
			return (NULL);
	}
	if (gnl_strchr(save, '\n') == NULL)
	{
		save = get_save(fd, save);
		if (save == NULL)
			return (NULL);
	}
	currentline = get_currentline(save);
	if (currentline == NULL)
		return (free_str_set_null(save));
	save = set_nextline(save);
	if (save == NULL)
		return (free_str_set_null(currentline));
	return (currentline);
}
