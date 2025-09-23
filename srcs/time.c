#include "GoL.h"

double	now_ms(void)
{
	struct timespec	ts;
	double			ms;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
		return (0.0);
	ms = (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
	return (ms);
}

void	init_clock_defaults(t_app *app)
{
	app->clk.target_tps = app->cfg.start_tps;
	app->clk.acc = 0.0;
	app->clk.last_ms = now_ms();
}

void	loop_do_steps(t_app *app, double dt_ms)
{
	double	step_ms;

	app->clk.acc += dt_ms;
	if (app->clk.acc < 0.0)
		app->clk.acc = 0.0;
	if (app->run != RUN_PLAY)
		return ;
	step_ms = 1000.0 / app->clk.target_tps;
	if (step_ms < 0.1)
		step_ms = 0.1;
	if (app->clk.acc >= step_ms)
	{
		world_step_dense(&app->world);
		app->clk.acc -= step_ms;
		if (app->clk.acc > step_ms)
			app->clk.acc = step_ms;
	}
}
