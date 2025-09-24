#include "GoL.h"

static int	zoom_step_up_int(int px)
{
	double	s;
	int		n;

	if (px < 1)
		px = 1;
	s = (double)px * 1.25;
	n = (int)ceil(s);
	if (n == px)
		n = px + 1;
	return (n);
}

static int	zoom_step_down_int(int px)
{
	double	s;
	int		n;

	if (px < 1)
		px = 1;
	s = (double)px / 1.25;
	n = (int)floor(s);
	if (n >= px)
		n = px - 1;
	if (n < 1)
		n = 1;
	return (n);
}

static int	view_zoom_compute_new_px(const t_view *view, int delta)
{
	int	old_px;
	int	new_px;

	old_px = view->cell_px;
	if (old_px < 1)
		old_px = 1;
	if (delta > 0)
		new_px = zoom_step_up_int(old_px);
	else if (delta < 0)
		new_px = zoom_step_down_int(old_px);
	else
		new_px = old_px;
	if (new_px < view->cell_px_min)
		new_px = view->cell_px_min;
	if (new_px > view->cell_px_max)
		new_px = view->cell_px_max;
	return (new_px);
}

static void	view_zoom_apply_keep_pivot(t_view *view, t_zoom_ctx ctx)
{
	double	world_x;
	double	world_y;

	world_x = (double)view->offset_x
		+ (double)ctx.pivot_screen.x / (double)ctx.old_cell_px;
	world_y = (double)view->offset_y
		+ (double)ctx.pivot_screen.y / (double)ctx.old_cell_px;
	view->cell_px = ctx.new_cell_px;
	view->offset_x = (int)(world_x
			- (double)ctx.pivot_screen.x / (double)ctx.new_cell_px);
	view->offset_y = (int)(world_y
			- (double)ctx.pivot_screen.y / (double)ctx.new_cell_px);
}

void	view_zoom_at_app(t_app *app, int delta, t_point pivot_screen)
{
	int			old_px;
	int			new_px;
	t_zoom_ctx	ctx;

	if (!app)
		return ;
	old_px = app->view.cell_px;
	if (old_px < 1)
		old_px = 1;
	new_px = view_zoom_compute_new_px(&app->view, delta);
	if (new_px == old_px)
		return ;
	ctx.new_cell_px = new_px;
	ctx.old_cell_px = old_px;
	ctx.pivot_screen = pivot_screen;
	view_zoom_apply_keep_pivot(&app->view, ctx);
	clamp_view_offsets(&app->view, &app->world, &app->gfx);
}
