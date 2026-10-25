#include "GoL.h"

int	on_key_press(int keycode, t_app *app)
{
	if (!app)
		return (0);
	key_action_on_press(app, keycode);
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
	key_action_on_release(app, keycode);
	if (keycode == KEY_UP)
		app->in.key_up = 0;
	if (keycode == KEY_DOWN)
		app->in.key_down = 0;
	if (keycode == KEY_LEFT)
		app->in.key_left = 0;
	if (keycode == KEY_RIGHT)
		app->in.key_right = 0;
	return (0);
}

int	on_focus_out(t_app *app)
{
	int	i;

	if (!app)
		return (0);
	app->in.key_up = 0;
	app->in.key_down = 0;
	app->in.key_left = 0;
	app->in.key_right = 0;
	app->in.pan_fraction_x = 0.0;
	app->in.pan_fraction_y = 0.0;
	app->in.mouse_dragging = 0;
	i = 0;
	while (i < KEY_ACTION_COUNT)
	{
		app->in.releases[i].held = 0;
		app->in.releases[i].pending = 0;
		i++;
	}
	return (0);
}
