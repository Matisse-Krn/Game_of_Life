#include "GoL.h"

void	init_view_defaults(t_app *app)
{
	int	cell_px;
	int	ox;
	int	oy;

	cell_px = 8;                 /* zoom par défaut */
	if (cell_px < 1) cell_px = 1;
	app->view.cell_px_min = 1;
	app->view.cell_px_max = 64;
	app->view.cell_px = cell_px;

	/* centre la vue sur le milieu du monde */
	ox = app->world.w / 2 - (app->gfx.win_w / (2 * cell_px));
	oy = app->world.h / 2 - (app->gfx.win_h / (2 * cell_px));
	if (ox < 0) ox = 0;
	if (oy < 0) oy = 0;
	app->view.offset_x = ox;
	app->view.offset_y = oy;
}
