#include <stdio.h>

enum	e_color
{
	RED		=	0xFF0000,
	GREEN	=	0x00FF00,
	BLUE	=	0x0000FF,
	WHITE	=	0xFFFFFF,
	BLACK	=	0x000000,
	GRAY	=	0x505050,
	PURPLE	=	0x4F00FF,
	SKY		=	0x00C1FF,
	BROWN	=	0x764B00,
};

int my_rgb(int r, int g, int b)
{
	int res;

	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	res = r;
	res <<= 8;
	res += g;
	res <<= 8;
	res += b;
	return (res);
}

int main()
{
	int res = my_rgb(255, 0, 0);
	printf("ori=%d, my=%d\n", RED, res);
	
}