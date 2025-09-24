#include "GoL.h"

int	on_mouse_press(int button, int x, int y, t_app *app)
{
	if (!app)
		return (0);
	app->in.mouse_last_x = x;
	app->in.mouse_last_y = y;
	if (button == MOUSE_BTN_LEFT)
	{
		app->in.mouse_dragging = 1;
		app->in.drag_px_acc_x = 0;
		app->in.drag_px_acc_y = 0;
	}
	if (button == MOUSE_WHEEL_UP)
		view_zoom_at_app(app, +1, (t_point){x, y});
	if (button == MOUSE_WHEEL_DOWN)
		view_zoom_at_app(app, -1, (t_point){x, y});
	return (0);
}

int	on_mouse_release(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (!app)
		return (0);
	if (button == MOUSE_BTN_LEFT)
		app->in.mouse_dragging = 0;
	return (0);
}

static void	mouse_store_last(t_app *app, int x, int y)
{
	app->in.mouse_last_x = x;
	app->in.mouse_last_y = y;
}

static void	mouse_pan_and_update(t_app *app, int cells_x, int cells_y)
{
	t_point	cells;

	if (cells_x == 0 && cells_y == 0)
		return ;
	cells.x = -cells_x;
	cells.y = -cells_y;
	view_pan_cells(&app->view, &app->world, cells, &app->gfx);
	app->in.drag_px_acc_x -= cells_x * app->view.cell_px;
	app->in.drag_px_acc_y -= cells_y * app->view.cell_px;
}

int	on_mouse_move(int x, int y, t_app *app)
{
	int	dx_px;
	int	dy_px;
	int	cells_x;
	int	cells_y;

	if (!app)
		return (0);
	if (!app->in.mouse_dragging)
	{
		mouse_store_last(app, x, y);
		return (0);
	}
	dx_px = x - app->in.mouse_last_x;
	dy_px = y - app->in.mouse_last_y;
	mouse_store_last(app, x, y);
	if (app->view.cell_px < 1)
		return (0);
	app->in.drag_px_acc_x += dx_px;
	app->in.drag_px_acc_y += dy_px;
	cells_x = app->in.drag_px_acc_x / app->view.cell_px;
	cells_y = app->in.drag_px_acc_y / app->view.cell_px;
	mouse_pan_and_update(app, cells_x, cells_y);
	return (0);
}
