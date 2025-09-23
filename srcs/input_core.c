#include "GoL.h"

void	input_begin_frame(t_input *in)
{
	if (!in)
		return ;
	in->mouse_wheel = 0;
}

int	on_key_press(int keycode, t_app *app)
{
	if (!app)
		return (0);
	if (keycode == KEY_ESC)
		app_destroy(app, 0);
	if (keycode == KEY_UP)
		app->in.key_up = 1;
	if (keycode == KEY_DOWN)
		app->in.key_down = 1;
	if (keycode == KEY_LEFT)
		app->in.key_left = 1;
	if (keycode == KEY_RIGHT)
		app->in.key_right = 1;
	if (keycode == KEY_N && app->run == RUN_PAUSED)
		app->in.req_step_once = 1;
	if (keycode == KEY_PGUP)
		app->in.req_speed_up = 1;
	if (keycode == KEY_PGDN)
		app->in.req_speed_down = 1;
	return (0);
}

int	on_key_release(int keycode, t_app *app)
{
	if (!app)
		return (0);
	if (keycode == KEY_UP)
		app->in.key_up = 0;
	if (keycode == KEY_DOWN)
		app->in.key_down = 0;
	if (keycode == KEY_LEFT)
		app->in.key_left = 0;
	if (keycode == KEY_RIGHT)
		app->in.key_right = 0;
	if (keycode == KEY_SPACE)
		app->in.req_toggle_run = 1;
	if (keycode == KEY_B)
		app->in.req_toggle_border = 1;
	if (keycode == KEY_C)
		app->in.req_clear_world = 1;
	if (keycode == KEY_R)
		app->in.req_reseed_world = 1;
	return (0);
}

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

void	apply_input_core(t_app *a)
{
	if (!a)
		return ;
	if (a->in.req_toggle_run)
	{
		a->in.req_toggle_run = 0;
		if (a->run == RUN_PLAY)
			a->run = RUN_PAUSED;
		else
			a->run = RUN_PLAY;
		a->clk.acc = 0.0;
	}
	if (a->in.req_step_once && a->run == RUN_PAUSED)
	{
		a->in.req_step_once = 0;
		world_step_dense(&a->world);
	}
	if (a->in.req_speed_up)
	{
		a->in.req_speed_up = 0;
		set_speed_hz(a, a->clk.target_tps * 1.25);
	}
	if (a->in.req_speed_down)
	{
		a->in.req_speed_down = 0;
		set_speed_hz(a, a->clk.target_tps / 1.25);
	}
	if (a->in.req_toggle_border)
	{
		a->in.req_toggle_border = 0;
		if (a->world.border == BORDER_TORE)
			a->world.border = BORDER_CLAMP;
		else
			a->world.border = BORDER_TORE;
	}
	if (a->in.req_clear_world)
	{
		a->in.req_clear_world = 0;
		world_clear(&a->world);
		a->clk.acc = 0.0;
	}
	if (a->in.req_reseed_world)
	{
		a->in.req_reseed_world = 0;
		world_seed_random(&a->world, a->cfg.start_density);
		a->clk.acc = 0.0;
	}
}
