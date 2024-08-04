#include "parse.h"

size_t ft_count_rows(char **d_str)
{
	size_t i;

	i = 0;
	while (d_str[i])
		i++;
	return (i);
}

char **ft_double_str_dup(char **d_str)
{
	char **res;
	size_t	i;
	size_t	y_count;

	y_count = ft_count_rows(d_str);
	res = (char **)malloc((y_count + 1) * sizeof(char *));
	i = 0;
	while (i < y_count)
	{
		res[i] = ft_strdup(d_str[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_free_double_str(char **d_str)
{
	size_t i;

	i = 0;
	if (!d_str)
		return ;
	while (d_str[i])
		free(d_str[i++]);
	free(d_str);
}

bool	ft_isequal(char *s1, char *s2)
{
	size_t len;

	len = ft_strlen(s1);
	return (len == ft_strlen(s2) && ft_strncmp(s1, s2, len) == 0);
}

void	ft_perror_exit(char *err_s, int exit_code)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	exit(exit_code);
}

bool	ft_perror_ret_false(char *err_s)
{
	ft_putendl_fd(err_s, STDERR_FILENO);
	return (false);
}

/// @param path not NULL
/// @param extention not NULL (.)start
bool	ft_validate_extention(char *path, char *extention)
{
	char *ptr;

	ptr = ft_strrchr(path, *extention);
	if (!ptr || ptr == path)
		return (false);
	return (ft_isequal(ptr, extention));
}

bool	ft_can_open(char *path, int open_mode)
{
	int fd;

	fd = open(path, open_mode);
	if (fd == -1)
		return(false);
	close(fd);
	return (true);
}

static size_t	get_start_count(const char *s1, const char *set)
{
	size_t	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static size_t	get_end_count(const char *s1, const char *set, size_t start)
{
	size_t	len;

	if (set == NULL)
		return (ft_strlen(s1) - 1);
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len -1]) != NULL)
		len--;
	return (len - 1);
}

char	*ft_strtrim_sepasets(const char *s1, const char *front_trim_set, const char *back_trim_set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (front_trim_set == NULL && back_trim_set == NULL)
		return ((char *)s1);
	start = get_start_count(s1, front_trim_set);
	end = get_end_count(s1, back_trim_set, start);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(&s1[start], 0, end - start + 1));
}
