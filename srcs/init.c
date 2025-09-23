#include "GoL.h"

int	app_init(t_app *app)
{
	app->init_status = INIT_NONE;
	if (!init_mlx_basics(app) || !init_mlx_image(app)
		|| !world_alloc(&app->world, 2048, 2048, BORDER_TORE))
		return (FALSE);
	app->init_status |= INIT_WORLD;
	app->cfg.start_density = 15;
	app->cfg.start_tps = 1.0;
	srand(time(NULL));
	world_seed_random(&app->world, app->cfg.start_density);
	init_view_defaults(app);
	init_clock_defaults(app);
	app->run = RUN_PLAY;
	return (TRUE);
}
