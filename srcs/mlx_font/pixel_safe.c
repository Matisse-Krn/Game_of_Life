#include "font5.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ---- clipping utils ---- */

static int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static int	rect_clip(t_rect *r, int w, int h)
{
	if (r->w <= 0 || r->h <= 0)
		return (0);
	if (r->x >= w || r->y >= h || r->x + r->w <= 0 || r->y + r->h <= 0)
		return (0);
	r->x = clampi(r->x, 0, w - 1);
	r->y = clampi(r->y, 0, h - 1);
	if (r->x + r->w > w)
		r->w = w - r->x;
	if (r->y + r->h > h)
		r->h = h - r->y;
	return (r->w > 0 && r->h > 0);
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
