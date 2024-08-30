//linux
// void	*mlx_xpm_file_to_image(t_xvar *xvar,char *filename,int *width,int *height)

//mac
// void	*mlx_xpm_file_to_image(mlx_ptr_t *xvar,char *file,int *width,int *height)


#include "libft.h"
#include "mlx.h"
#include "utils.h"

#if defined(__linux__)

void	*ft_x_mlx_xpm_file_to_image(t_xvar *xvar,char *filename, int *width,int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(xvar,filename,width,height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_xpm_file_to_image error", 1);
	return (ret);
}
#else

void *ft_x_mlx_xpm_file_to_image(void *mlx_ptr,char *filename,int *width,int *height)
{
  void	*ret;

	ret = mlx_xpm_file_to_image(mlx_ptr,filename,width,height);
	if (ret == NULL)
		ft_my_perror_exit("mlx_xpm_file_to_image error", 1);
	return (ret);
}

#endif