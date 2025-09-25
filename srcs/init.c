#include "GoL.h"

int	app_init(t_app *app)
{
	app->init_status = INIT_NONE;
	app->ui_font = font_create();
	if (app->ui_font)
		app->init_status |= INIT_FONT;
	if (!init_mlx_basics(app) || !init_mlx_image(app)
		|| !world_alloc(&app->world, 2048, 2048, BORDER_TORE))
		return (FALSE);
	app->init_status |= INIT_WORLD;
	app->cfg.start_density = 10;
	app->cfg.start_tps = 1.0;
	srand(time(NULL));
	world_seed_random(&app->world, app->cfg.start_density);
	init_view_defaults(app);
	init_clock_defaults(app);
	app->run = RUN_PLAY;
	app->hud_visible = TRUE;
	return (TRUE);
}
