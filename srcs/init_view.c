#include "GoL.h"

void	init_view_defaults(t_app *app)
{
	int	cell_px;
	int	offset_x;
	int	offset_y;

	cell_px = 8;
	if (cell_px < 1)
		cell_px = 1;
	app->view.cell_px_min = 1;
	app->view.cell_px_max = 64;
	app->view.cell_px = cell_px;
	offset_x = app->world.w / 2 - (app->gfx.win_w / (2 * cell_px));
	offset_y = app->world.h / 2 - (app->gfx.win_h / (2 * cell_px));
	if (offset_x < 0)
		offset_x = 0;
	if (offset_y < 0)
		offset_y = 0;
	app->view.offset_x = offset_x;
	app->view.offset_y = offset_y;
}
