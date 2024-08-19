/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:39:13 by tozeki            #+#    #+#             */
/*   Updated: 2024/08/15 20:09:53 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h> //size_t
# include <limits.h> //LONG_MAX & MIN
# include <stdlib.h> //malloc
# include <unistd.h> //write
# include <fcntl.h> //open
# include <stdbool.h> //bool
# include <stdio.h> //perror
# include "get_next_line.h"

bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *buf, int ch, size_t n);
void	*ft_bzero(void *buf, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *bigs, const char *lits, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
// original
size_t	ft_count_rows(char **d_str);
char	**ft_double_str_dup(char **d_str);
void	ft_free_double_str(char **d_str);
bool	ft_isequal(char *s1, char *s2);
bool	ft_my_perror_ret_false(char *err_s);
char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set,
			const char *back_trim_set);
bool	ft_validate_extention(char *path, char *extention);
char	*ft_itonbase(int num, unsigned int base);
// open 
bool	ft_can_open(char *path, int open_mode);
//exit
void	ft_my_perror_exit(char *err_s, int exit_code);
void	*ft_x_calloc(size_t count, size_t size);
char	*ft_x_itoa(int n);
void	*ft_x_malloc(size_t size);
void	*ft_x_realloc(void *ptr, size_t size);
char	**ft_x_split(const char *s, char c);
char	*ft_x_strdup(const char *s1);
char	*ft_x_strjoin(const char *s1, const char *s2);
char	*ft_x_strtrim(const char *s1, const char *set);
char	*ft_x_substr(const char *s, unsigned int start, size_t len);
char	**ft_x_double_str_dup(char **d_str);
char	*ft_x_strtrim_sepasets(const char *s1, const char *front_trim_set,
			const char *back_trim_set);
//perror
void	ft_perror_exit(char *err_title, int exit_code);

#endif