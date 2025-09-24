#include "GoL.h"

static double	clamp_range(double v, double vmin, double vmax)
{
	if (v < vmin)
		return (vmin);
	if (v > vmax)
		return (vmax);
	return (v);
}

static void	set_speed_hz(t_app *a, double hz)
{
	hz = clamp_range(hz, TPS_MIN, TPS_MAX);
	a->clk.target_tps = hz;
}

void	handle_speed_adjust_requests(t_app *app)
{
	if (!app)
		return ;
	if (app->in.req_speed_up)
	{
		app->in.req_speed_up = 0;
		set_speed_hz(app, app->clk.target_tps * 1.25);
	}
	if (app->in.req_speed_down)
	{
		app->in.req_speed_down = 0;
		set_speed_hz(app, app->clk.target_tps / 1.25);
	}
}
