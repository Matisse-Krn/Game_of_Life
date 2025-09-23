#include "GoL.h"

static int	clip_prepare(const t_img *img, t_rect *r)
{
	if (!img || !img->addr || r->w <= 0 || r->h <= 0)
		return (0);
	if (r->x < 0)
	{
		r->w += r->x;
		r->x = 0;
	}
	if (r->y < 0)
	{
		r->h += r->y;
		r->y = 0;
	}
	if (r->x >= img->w || r->y >= img->h)
		return (0);
	if (r->w <= 0 || r->h <= 0)
		return (0);
	return (1);
}

static void	clip_bounds(const t_img *img, t_rect *r)
{
	if (r->x + r->w > img->w)
		r->w = img->w - r->x;
	if (r->y + r->h > img->h)
		r->h = img->h - r->y;
}

void	frame_fill_rect(t_img *img, t_rect rect, unsigned int argb)
{
	int				y;
	int				x;
	int				ex;
	unsigned int	*line;

	if (!clip_prepare(img, &rect))
		return ;
	clip_bounds(img, &rect);
	ex = rect.x + rect.w;
	y = rect.y;
	while (y < rect.y + rect.h)
	{
		x = rect.x;
		line = (unsigned int *)(img->addr
				+ (size_t)y * (size_t)img->ll
				+ (size_t)rect.x * (size_t)(img->bpp / 8));
		while (x < ex)
		{
			*line = argb;
			line++;
			x++;
		}
		y++;
	}
}
