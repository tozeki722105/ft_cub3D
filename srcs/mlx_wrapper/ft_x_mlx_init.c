#include "libft.h"
#include "mlx.h"
#include "utils.h"

void	*ft_x_mlx_init()
{
	void	*ret;

	ret = mlx_init();
	if (ret == NULL)
		ft_my_perror_exit("mlx_init", 1);
	return (ret);
}
