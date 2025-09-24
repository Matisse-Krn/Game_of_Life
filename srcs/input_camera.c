#include "GoL.h"

static double	camera_cells_per_sec(const t_view *v)
{
	double	px;

	px = (double)v->cell_px;
	if (px < 1.0)
		px = 1.0;
	return (CAMERA_BASE_PX_PER_SEC / px);
}

static void	camera_pan_from_keys(t_app *app, double dt_ms)
{
	double	speed_cells_per_sec;
	double	vel_x_cells_per_sec;
	double	vel_y_cells_per_sec;
	t_point	delta_cells;

	speed_cells_per_sec = camera_cells_per_sec(&app->view);
	vel_x_cells_per_sec = 0.0;
	vel_y_cells_per_sec = 0.0;
	if (app->in.key_left)
		vel_x_cells_per_sec = vel_x_cells_per_sec - speed_cells_per_sec;
	if (app->in.key_right)
		vel_x_cells_per_sec = vel_x_cells_per_sec + speed_cells_per_sec;
	if (app->in.key_up)
		vel_y_cells_per_sec = vel_y_cells_per_sec - speed_cells_per_sec;
	if (app->in.key_down)
		vel_y_cells_per_sec = vel_y_cells_per_sec + speed_cells_per_sec;
	delta_cells.x = (int)(vel_x_cells_per_sec * dt_ms / 1000.0);
	delta_cells.y = (int)(vel_y_cells_per_sec * dt_ms / 1000.0);
	if (delta_cells.x != 0 || delta_cells.y != 0)
		view_pan_cells(&app->view, &app->world, delta_cells, &app->gfx);
}

static void	camera_zoom_from_requests(t_app *app)
{
	t_point	center_px;

	if (!app->in.req_zoom_in && !app->in.req_zoom_out)
		return ;
	center_px.x = app->gfx.win_w / 2;
	center_px.y = app->gfx.win_h / 2;
	if (app->in.req_zoom_in)
		view_zoom_at_app(app, +1, (t_point){center_px.x, center_px.y});
	if (app->in.req_zoom_out)
		view_zoom_at_app(app, -1, (t_point){center_px.x, center_px.y});
	app->in.req_zoom_in = 0;
	app->in.req_zoom_out = 0;
}

void	apply_input_camera(t_app *app, double dt_ms)
{
	if (!app)
		return ;
	camera_pan_from_keys(app, dt_ms);
	camera_zoom_from_requests(app);
}
