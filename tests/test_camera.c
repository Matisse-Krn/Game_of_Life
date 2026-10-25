#include "GoL.h"
#include <assert.h>
#include <stdio.h>

static t_app	make_app(int cell_px)
{
	t_app	app;

	app = (t_app){0};
	app.world.w = 2048;
	app.world.h = 2048;
	app.gfx.win_w = 640;
	app.gfx.win_h = 480;
	app.view.cell_px = cell_px;
	app.view.cell_px_min = 1;
	app.view.cell_px_max = 128;
	return (app);
}

static void	test_fractional_pan(void)
{
	t_app	app;
	int		i;

	app = make_app(64);
	app.in.key_right = 1;
	i = 0;
	while (i++ < 20)
		apply_input_camera(&app, 16.0);
	assert(app.view.offset_x >= 3 && app.view.offset_x <= 4);
	app.in.key_right = 0;
	apply_input_camera(&app, 16.0);
	assert(app.in.pan_fraction_x == 0.0);
	app.in.key_left = 1;
	i = 0;
	while (i++ < 20)
		apply_input_camera(&app, 16.0);
	assert(app.view.offset_x == 0);
}

static void	test_speed_and_large_delta(void)
{
	t_app	app;
	int		i;

	app = make_app(8);
	app.in.key_right = 1;
	i = 0;
	while (i++ < 20)
		apply_input_camera(&app, 16.0);
	assert(app.view.offset_x >= 31 && app.view.offset_x <= 32);
	app = make_app(8);
	app.in.key_right = 1;
	apply_input_camera(&app, 100000.0);
	assert(app.view.offset_x <= 25);
	assert(app.view.offset_x > 0);
	app = make_app(8);
	app.in.key_right = 1;
	apply_input_camera(&app, NAN);
	apply_input_camera(&app, INFINITY);
	assert(app.view.offset_x == 0);
	assert(app.in.pan_fraction_x == 0.0);
}

int	main(void)
{
	test_fractional_pan();
	test_speed_and_large_delta();
	puts("Camera movement tests: OK");
	return (0);
}
