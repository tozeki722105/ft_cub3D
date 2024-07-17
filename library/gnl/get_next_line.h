/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:38:01 by tozeki            #+#    #+#             */
/*   Updated: 2023/05/22 18:01:06 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h> //size_t
# include <unistd.h> //ssize_t

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*append_str(char *dest, char *src, ssize_t count);
char	*get_save(int fd, char *save);
char	*get_currentline(char *save);
char	*set_nextline(char *save);
void	*ft_calloc(size_t count, size_t size);
char	*free_str_set_null(char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

#endif
