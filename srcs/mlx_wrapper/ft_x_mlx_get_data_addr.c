#include "libft.h"
#include "mlx.h"
#include "utils.h"

void *ft_x_mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,int *size_line, int *endian)
{
  void	*ret;

	ret = mlx_get_data_addr(img_ptr,bits_per_pixel,size_line,endian);
	if (ret == NULL)
		ft_my_perror_exit("mlx_get_data_addr error", 1);
	return (ret);
}