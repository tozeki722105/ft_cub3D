#include "libft.h"
#include "mlx.h"
#include "utils.h"

void	*ft_x_mlx_new_image(t_xvar *xvar,int width, int height)
{
	void	*ret;

	ret = mlx_new_image(xvar,width, height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_image", 1);
	return (ret);
}