#include "GoL.h"

static void	handle_toggle_run(t_app *app)
{
	if (!app)
		return ;
	if (!app->in.req_toggle_run)
		return ;
	app->in.req_toggle_run = 0;
	if (app->run == RUN_PLAY)
		app->run = RUN_PAUSED;
	else
		app->run = RUN_PLAY;
	app->clk.acc = 0.0;
}

static void	handle_step_once_when_paused(t_app *app)
{
	if (!app)
		return ;
	if (!app->in.req_step_once)
		return ;
	if (app->run != RUN_PAUSED)
		return ;
	app->in.req_step_once = 0;
	world_step_dense(&app->world);
}

static void	handle_toggle_border_mode(t_app *app)
{
	if (!app)
		return ;
	if (!app->in.req_toggle_border)
		return ;
	app->in.req_toggle_border = 0;
	if (app->world.border == BORDER_TORE)
		app->world.border = BORDER_CLAMP;
	else
		app->world.border = BORDER_TORE;
}

static void	handle_world_clear_and_reseed(t_app *app)
{
	if (!app)
		return ;
	if (app->in.req_clear_world)
	{
		app->in.req_clear_world = 0;
		world_clear(&app->world);
		app->clk.acc = 0.0;
	}
	if (app->in.req_reseed_world)
	{
		app->in.req_reseed_world = 0;
		world_seed_random(&app->world, app->cfg.start_density);
		app->clk.acc = 0.0;
	}
}

void	apply_input_core(t_app *app)
{
	if (!app)
		return ;
	handle_toggle_run(app);
	handle_step_once_when_paused(app);
	handle_speed_adjust_requests(app);
	handle_toggle_border_mode(app);
	handle_world_clear_and_reseed(app);
}
