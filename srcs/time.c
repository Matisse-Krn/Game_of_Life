#include "GoL.h"

#define MAX_FRAME_DT_MS 250.0
#define MAX_CATCHUP_STEPS 8

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
	int		steps;

	if (!app)
		return ;
	if (app->run != RUN_PLAY)
	{
		app->clk.acc = 0.0;
		return ;
	}
	if (!isfinite(dt_ms) || dt_ms < 0.0
		|| !isfinite(app->clk.target_tps) || app->clk.target_tps <= 0.0)
		return ;
	if (dt_ms > MAX_FRAME_DT_MS)
		dt_ms = MAX_FRAME_DT_MS;
	if (!isfinite(app->clk.acc) || app->clk.acc < 0.0)
		app->clk.acc = 0.0;
	app->clk.acc += dt_ms;
	step_ms = 1000.0 / app->clk.target_tps;
	if (step_ms < 0.1)
		step_ms = 0.1;
	steps = 0;
	while (app->clk.acc >= step_ms && steps < MAX_CATCHUP_STEPS)
	{
		world_step_dense(&app->world);
		app->clk.acc -= step_ms;
		steps++;
	}
	if (app->clk.acc >= step_ms)
		app->clk.acc = fmod(app->clk.acc, step_ms);
}
