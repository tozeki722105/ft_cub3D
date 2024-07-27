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