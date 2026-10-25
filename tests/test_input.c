#include "GoL.h"
#include <assert.h>
#include <stdio.h>

static double	fake_now;

double	now_ms(void)
{
	return (fake_now);
}

int	app_destroy(t_app *app, int exit_code)
{
	(void)app;
	return (exit_code);
}

static void	test_autorepeat_filter(void)
{
	t_app	app;

	app = (t_app){0};
	app.hud_visible = 1;
	fake_now = 100.0;
	on_key_press(KEY_H, &app);
	on_key_release(KEY_H, &app);
	fake_now = 110.0;
	apply_pending_key_actions(&app);
	assert(!app.in.req_toggle_hud);
	on_key_press(KEY_H, &app);
	fake_now = 200.0;
	apply_pending_key_actions(&app);
	assert(!app.in.req_toggle_hud);
	on_key_release(KEY_H, &app);
	fake_now = 240.0;
	apply_pending_key_actions(&app);
	assert(app.in.req_toggle_hud);
	handle_toggle_hud(&app);
	assert(!app.hud_visible && !app.in.req_toggle_hud);
	fake_now = 400.0;
	apply_pending_key_actions(&app);
	assert(!app.in.req_toggle_hud);
}

static void	test_other_release_actions(void)
{
	t_app	app;

	app = (t_app){0};
	fake_now = 100.0;
	on_key_press(KEY_SPACE, &app);
	on_key_press(KEY_B, &app);
	on_key_press(KEY_C, &app);
	on_key_press(KEY_R, &app);
	on_key_release(KEY_SPACE, &app);
	on_key_release(KEY_B, &app);
	on_key_release(KEY_C, &app);
	on_key_release(KEY_R, &app);
	fake_now = 150.0;
	apply_pending_key_actions(&app);
	assert(app.in.req_toggle_run);
	assert(app.in.req_toggle_border);
	assert(app.in.req_clear_world);
	assert(app.in.req_reseed_world);
	assert(!app.in.req_toggle_hud);
	app.in.req_toggle_run = 0;
	app.in.req_toggle_border = 0;
	app.in.req_clear_world = 0;
	app.in.req_reseed_world = 0;
	apply_pending_key_actions(&app);
	assert(!app.in.req_toggle_run && !app.in.req_reseed_world);
	on_key_release(KEY_SPACE, &app);
	apply_pending_key_actions(&app);
	assert(!app.in.req_toggle_run);
}

static void	test_continuous_keys(void)
{
	t_app	app;

	app = (t_app){0};
	on_key_press(KEY_LEFT, &app);
	assert(app.in.key_left == 1);
	on_key_release(KEY_LEFT, &app);
	assert(app.in.key_left == 0);
	app.run = RUN_PAUSED;
	on_key_press(KEY_N, &app);
	assert(app.in.req_step_once == 1);
	on_key_press(KEY_UP, &app);
	on_key_press(KEY_H, &app);
	app.in.mouse_dragging = 1;
	app.in.pan_fraction_x = 0.6;
	on_focus_out(&app);
	assert(!app.in.key_up && !app.in.key_left);
	assert(!app.in.mouse_dragging && app.in.pan_fraction_x == 0.0);
	assert(!app.in.releases[KEY_ACTION_HUD].held);
}

int	main(void)
{
	test_autorepeat_filter();
	test_other_release_actions();
	test_continuous_keys();
	puts("Input event tests: OK");
	return (0);
}
