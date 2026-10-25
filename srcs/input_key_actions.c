#include "GoL.h"

#define KEY_RELEASE_GRACE_MS 35.0

static int	key_action_index(int keycode)
{
	if (keycode == KEY_SPACE)
		return (KEY_ACTION_RUN);
	if (keycode == KEY_B)
		return (KEY_ACTION_BORDER);
	if (keycode == KEY_C)
		return (KEY_ACTION_CLEAR);
	if (keycode == KEY_R)
		return (KEY_ACTION_RESEED);
	if (keycode == KEY_H)
		return (KEY_ACTION_HUD);
	return (-1);
}

void	key_action_on_press(t_app *app, int keycode)
{
	int	idx;

	if (!app)
		return ;
	idx = key_action_index(keycode);
	if (idx < 0)
		return ;
	app->in.releases[idx].pending = 0;
	app->in.releases[idx].held = 1;
}

void	key_action_on_release(t_app *app, int keycode)
{
	int	idx;

	if (!app)
		return ;
	idx = key_action_index(keycode);
	if (idx < 0 || !app->in.releases[idx].held)
		return ;
	app->in.releases[idx].held = 0;
	app->in.releases[idx].pending = 1;
	app->in.releases[idx].released_ms = now_ms();
}

static void	request_key_action(t_app *app, int idx)
{
	if (idx == KEY_ACTION_RUN)
		app->in.req_toggle_run = 1;
	else if (idx == KEY_ACTION_BORDER)
		app->in.req_toggle_border = 1;
	else if (idx == KEY_ACTION_CLEAR)
		app->in.req_clear_world = 1;
	else if (idx == KEY_ACTION_RESEED)
		app->in.req_reseed_world = 1;
	else if (idx == KEY_ACTION_HUD)
		app->in.req_toggle_hud = 1;
}

void	apply_pending_key_actions(t_app *app)
{
	double	now;
	int		i;

	if (!app)
		return ;
	now = now_ms();
	i = 0;
	while (i < KEY_ACTION_COUNT)
	{
		if (app->in.releases[i].pending
			&& now - app->in.releases[i].released_ms
			>= KEY_RELEASE_GRACE_MS)
		{
			app->in.releases[i].pending = 0;
			request_key_action(app, i);
		}
		i++;
	}
}
