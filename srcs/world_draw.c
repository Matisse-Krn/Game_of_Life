#include "GoL.h"

static t_rect	visible_cells_rect(const t_world *world,
		const t_view *view, const t_img *dst)
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

static void	draw_cells(const t_world *world,
		const t_view *view, t_img *dst, t_rect vis)
{
	t_rect	r;
	int		x;
	int		y;
	int		idx;

	r.w = view->cell_px;
	r.h = view->cell_px;
	y = 0;
	while (y < vis.h)
	{
		r.y = y * view->cell_px;
		x = 0;
		idx = (vis.y + y) * world->w + vis.x;
		while (x < vis.w)
		{
			r.x = x * view->cell_px;
			if (world->cur[idx])
				frame_fill_rect(dst, r, 0xFFE6E6E6u);
			idx++;
			x++;
		}
		y++;
	}
}

void	draw_world_to_frame(const t_world *world,
		const t_view *view, t_img *dst)
{
	t_rect	vis;

	if (!world || !view || !dst || !dst->addr || view->cell_px <= 0)
		return ;
	clear_frame(dst);
	vis = visible_cells_rect(world, view, dst);
	draw_cells(world, view, dst, vis);
}
