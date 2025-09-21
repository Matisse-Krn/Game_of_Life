#include "GoL.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x >= img->w || x < 0 || y >= img->h || y < 0)
		return ;
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_frame(t_img *img)
{
	if (!img || !img->addr)
		return ;
	ft_bzero(img->addr, (size_t)img->ll * (size_t)img->h);
}
