#include "font5.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

static int	rect_clip(t_rect *r, int w, int h)
{
	int64_t	x0;
	int64_t	y0;
	int64_t	x1;
	int64_t	y1;

	if (w <= 0 || h <= 0 || r->w <= 0 || r->h <= 0)
		return (0);
	x0 = r->x;
	y0 = r->y;
	x1 = x0 + r->w;
	y1 = y0 + r->h;
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x1 > w)
		x1 = w;
	if (y1 > h)
		y1 = h;
	if (x1 <= x0 || y1 <= y0)
		return (0);
	r->x = (int)x0;
	r->y = (int)y0;
	r->w = (int)(x1 - x0);
	r->h = (int)(y1 - y0);
	return (1);
}

/* ---- API sûre ---- */

void	pixel_put_safe(t_img *img, int x, int y, int color)
{
	int	w;
	int	h;

	if (!img)
		return ;
	w = font5_img_w(img);
	h = font5_img_h(img);
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	my_mlx_pixel_put(img, x, y, color);
}

void	fill_rect_safe(t_img *img, t_rect r, int color)
{
	int	x;
	int	y;
	int	w;
	int	h;

	if (!img)
		return ;
	w = font5_img_w(img);
	h = font5_img_h(img);
	if (!rect_clip(&r, w, h))
		return ;
	y = 0;
	while (y < r.h)
	{
		x = 0;
		while (x < r.w)
		{
			my_mlx_pixel_put(img, r.x + x, r.y + y, color);
			x++;
		}
		y++;
	}
}
