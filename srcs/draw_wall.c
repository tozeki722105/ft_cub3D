#include "ogv1.h"
#include "calc.h"


int calc_img_x(t_intersection inter, t_src img, int map_panel_side)
{
	int img_offset;
	
	if (inter.touching_axis == HORIZONTAL)
		img_offset = (int)fabs((double)(inter.origin_offset - inter.x));
	else
		img_offset = (int)fabs((double)(inter.origin_offset - inter.y));
	return ((img.width * img_offset) / map_panel_side);
}


t_src get_img(t_mlx *mlx, t_intersection inter)
{
	if (inter.touching_axis == HORIZONTAL)
	{
		if (is_up(inter.degree))
			return (mlx->textures.north);
		else
			return (mlx->textures.south);
	}
	else
	{
		if (is_right(inter.degree))
			return (mlx->textures.east);
		else
			return (mlx->textures.west);
	}
}

void draw_vertical_line_of_wall(t_mlx *mlx, t_intersection inter, size_t put_x)
{
	int put_y;
	size_t wall_i;
	size_t img_x;
	size_t img_y;
	t_src img;

	img = get_img(mlx, inter);
	img_x = calc_img_x(inter, img, mlx->map.panel_side);
	put_y = (WINDOW_HEIGHT / 2) - ((int)inter.wall_height / 2);
	wall_i = 0;
	while (wall_i < (int)inter.wall_height)
	{

		if (put_y >= 0 && put_y < WINDOW_HEIGHT)
		{
			img_y = (img.height * wall_i) / inter.wall_height;
			put_pixel(&(mlx->img), put_x, put_y, pick_color(&img, img_x, img_y));
		}
		put_y++;
		wall_i++;
	}
}


# define TEST_LOG "log.txt"
#include <fcntl.h>
void draw_wall(t_mlx *mlx, int start)
{
	double draw_angle;
	double step;
	size_t x;
	t_intersection inter;

	draw_angle = fix_angle(mlx->player.angle + (FOV / 2));
	step = (double)FOV / ((double)WINDOW_WIDTH);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		inter = calc_intersection(mlx, draw_angle);
		draw_vertical_line_of_wall(mlx, inter, x);
		draw_angle = fix_angle(draw_angle - step);
		x++;
	}
}

	// int fd = open(TEST_LOG, O_RDWR | O_CREAT | O_TRUNC);
	// 	prev = inter;
	// dprintf(fd, "\n");
	// size_t c = 0;
	// t_intersection prev;
		// if (x > 0 && abs(prev.x - inter.x) < 0.001 && abs(prev.y - inter.y) < 0.001)
		// 	c++;
	// if (700 < c)
	// 	printf("bad=%lf\n", );

	
// double	deg_to_rad(double deg)
// {
// 	return (M_PI * deg / 180);
// }

// double	rad_to_deg(double rad)
// {
// 	return (rad * 180 / M_PI);
// }

// double calc_angle(t_mlx *mlx, double draw_angle, int x)
// {
// 	double win_half = WINDOW_WIDTH / 2;
// 	double rad_of_half_fov = deg_to_rad(FOV / 2);
// 	return (draw_angle - rad_to_deg(atan(tan_wrap(rad_of_half_fov) * x / win_half)));
// }

// draw_angle = fix_angle(calc_angle(mlx, draw_angle, x));