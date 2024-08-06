#include "parse.h"

/// @brief sapace_only_str is true 
static bool	is_map_str(char *str)
{
	if (*str == '\n')
		return (false);
	while (*str && *str != '\n')
	{
		if (!is_map_element(*str))
			return (false);
		str++;
	}
	return (true);
}

t_line_kind	get_line_kind(char *str)
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

char *extract_val(char *str, t_line_kind kind)
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
