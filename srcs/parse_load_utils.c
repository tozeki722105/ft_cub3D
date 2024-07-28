#include "parse.h"

t_parse_kind	parse_kind(char *str)
{
	if (*str == '\n')
		return (KIND_NEWLINE);
	if (is_map_str(str))
		return (KIND_MAP);
	if (*str == 'N' && *(str + sizeof(char)) == 'O')
		return (KIND_NORTH);
	if (*str == 'S' && *(str + sizeof(char)) == 'O')
		return (KIND_SOUTH);
	if (*str == 'W' && *(str + sizeof(char)) == 'E')
		return (KIND_WEST);
	if (*str == 'E' && *(str + sizeof(char)) == 'A')
		return (KIND_EAST);
	if (*str == 'F')
		return (KIND_FLOOR);
	if (*str == 'C')
		return (KIND_CEILING);
	else
		return (KIND_FALSE);
}

char *extract_val(char *str, t_parse_kind kind)
{
	size_t	identifer_len;
	char	*val_include_space;
	char	*val;

	if (is_wall(kind))
		identifer_len = 2;
	else
		identifer_len = 1;
	val_include_space = ft_substr(str, identifer_len, ft_strlen(str) - identifer_len);
	val = ft_strtrim(val_include_space, " \t\n");
	free(val_include_space);
	return (val);
}

bool	ft_is_access(char *path, int open_mode)
{
	int fd;

	fd = open(path, open_mode);
	if (fd == -1)
		return(false);
	close(fd);
	return (true);
}

void	add_wall(t_loader *loader, t_parse_kind kind, char *str)
{
	char *val;

	val = extract_val(str, kind);
	// if (!ft_is_access(val, O_RDONLY))
	// 	ft_perror_exit("The texture path is incorrect", 0);
	if (kind == KIND_NORTH)
		loader->north_path = val;
	else if (kind == KIND_SOUTH)
		loader->south_path = val;
	else if (kind == KIND_WEST)
		loader->west_path = val;
	else if (kind == KIND_EAST)
		loader->east_path = val;
}




