#include "GoL.h"

int	key_pressed(int keycode, t_app *app)
{
	if (keycode == ESC)
		app_destroy(app, 0);
	return (0);
}
