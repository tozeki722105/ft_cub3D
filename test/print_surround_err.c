void	print_err(char **map_data, size_t y, size_t x)
{
	// printf("%c", map_data[y - 1][x - 1]);
	printf("%c", map_data[y - 1][x]);
	// printf("%c", map_data[y - 1][x + 1]);
	printf(";\n");
	printf("%c", map_data[y][x - 1]);
	printf("%c", map_data[y][x]);
	printf("%c", map_data[y][x + 1]);
	printf(";\n");
	// printf("%c", map_data[y + 1][x - 1]);
	printf("%c", map_data[y + 1][x]);
	// printf("%c", map_data[y + 1][x + 1]);
	printf(";\n");
}