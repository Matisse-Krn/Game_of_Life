#include "GoL.h"

static t_rect	visible_cells_rect(const t_world *world, const t_view *view, const t_img *dst)
{
	t_rect	rect;

	rect.x = view->offset_x;
	rect.y = view->offset_y;
	if (rect.x < 0)
		rect.x = 0;
	if (rect.y < 0)
		rect.y = 0;
	rect.w = dst->w / view->cell_px + 1;
	rect.h = dst->h / view->cell_px + 1;
	if (rect.x + rect.w > world->w)
		rect.w = world->w - rect.x;
	if (rect.y + rect.h > world->h)
		rect.h = world->h - rect.y;
	if (rect.w < 0)
		rect.w = 0;
	if (rect.h < 0)
		rect.h = 0;
	return (rect);
}

static void	frame_fill_rect(t_img *img, t_rect rect, unsigned int argb)
{
	int				y;
	int				end_x;
	int				end_y;
	unsigned int	*line;

	if (!img || !img->addr || rect.w <= 0 || rect.h <= 0)
		return ;
	if (rect.x < 0)
	{
		rect.w += rect.x;
		rect.x = 0;
	}
	if (rect.y < 0)
	{
		rect.h += rect.y;
		rect.y = 0;
	}
	if (rect.x >= img->w || rect.y >= img->h)
		return ;
	if (rect.x + rect.w > img->w)
		rect.w = img->w - rect.x;
	if (rect.y + rect.h > img->h)
		rect.h = img->h - rect.y;
	end_x = rect.x + rect.w;
	end_y = rect.y + rect.h;
	y = rect.y;
	while (y < end_y)
	{
		line = (unsigned int *)(img->addr + (size_t)y * (size_t)img->ll
				+ (size_t)rect.x * (size_t)(img->bpp / 8));
		while (rect.x < end_x) /* on réutilise rect.x comme curseur */
		{
			*line = argb;
			line++;
			rect.x++;
		}
		rect.x = end_x - rect.w; /* restore x de départ pour la ligne suivante */
		y++;
	}
}

void	draw_world_to_frame(const t_world *world, const t_view *view, t_img *dst)
{
	t_rect	vis;
	t_rect	cell_px;
	int		x;
	int		y;

	if (!world || !view || !dst || !dst->addr || view->cell_px <= 0)
		return ;
	clear_frame(dst);
	vis = visible_cells_rect(world, view, dst);
	y = 0;
	while (y < vis.h)
	{
		x = 0;
		while (x < vis.w)
		{
			if (world->cur[(vis.y + y) * world->w + (vis.x + x)])
			{
				cell_px.x = (x * view->cell_px);
				cell_px.y = (y * view->cell_px);
				cell_px.w = view->cell_px;
				cell_px.h = view->cell_px;
				frame_fill_rect(dst, cell_px, 0xFFE6E6E6u);
			}
			x++;
		}
		y++;
	}
}

