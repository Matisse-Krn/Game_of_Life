#include "GoL.h"

void	clamp_view_offsets(t_view *v, const t_world *w, const t_gfx *g)
{
	int	vis_w;
	int	vis_h;
	int	max_x;
	int	max_y;

	if (v->cell_px < 1)
		v->cell_px = 1;
	vis_w = g->win_w / v->cell_px;
	vis_h = g->win_h / v->cell_px;
	max_x = w->w - vis_w;
	max_y = w->h - vis_h;
	if (max_x < 0)
		max_x = 0;
	if (max_y < 0)
		max_y = 0;
	if (v->offset_x < 0)
		v->offset_x = 0;
	if (v->offset_y < 0)
		v->offset_y = 0;
	if (v->offset_x > max_x)
		v->offset_x = max_x;
	if (v->offset_y > max_y)
		v->offset_y = max_y;
}

void	view_pan_cells(t_view *view, const t_world *world,
	t_point delta_cells, const t_gfx *gfx)
{
	if (!view || !world || !gfx)
		return ;
	view->offset_x = view->offset_x + delta_cells.x;
	view->offset_y = view->offset_y + delta_cells.y;
	clamp_view_offsets(view, world, gfx);
}
