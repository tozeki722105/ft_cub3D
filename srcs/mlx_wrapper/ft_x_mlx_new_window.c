#include "libft.h"
#include "mlx.h"
#include "utils.h"


void	*ft_x_mlx_new_window(t_xvar *xvar,int size_x,int size_y,char *title)
{
	void	*ret;

	ret = mlx_new_window(xvar,size_x,size_y,title);
	if (ret == NULL)
		ft_my_perror_exit("mlx_new_window", 1);
	return (ret);
}