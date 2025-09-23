#include "GoL.h"

int	app_init(t_app *app)
{
	app->init_status = INIT_NONE;
	if (!init_mlx_basics(app) || !init_mlx_image(app)
		|| !world_alloc(&app->world, 4096, 4096, BORDER_TORE))
		return (FALSE);
	app->init_status |= INIT_WORLD;
	srand(time(NULL));
	world_seed_random(&app->world, 15);
	init_view_defaults(app);
	init_clock_defaults(app);
	app->run = RUN_PLAY;
	return (TRUE);
}
