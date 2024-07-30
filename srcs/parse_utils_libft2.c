#include "parse.h"

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