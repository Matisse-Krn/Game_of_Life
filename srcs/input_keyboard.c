#include "GoL.h"

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
	if (keycode == KEY_H)
		app->in.req_toggle_hud = 1;
	if (keycode == KEY_N && app->run == RUN_PAUSED)
		app->in.req_step_once = 1;
	if (keycode == KEY_PGUP)
		app->in.req_speed_up = 1;
	if (keycode == KEY_PGDN)
		app->in.req_speed_down = 1;
	if (keycode == KEY_PLUS || keycode == KEY_KP_ADD)
		app->in.req_zoom_in = 1;
	if (keycode == KEY_MINUS || keycode == KEY_KP_SUB)
		app->in.req_zoom_out = 1;
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
