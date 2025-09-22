#include "GoL.h"

static int	loop_hook(t_app *app)
{
	clear_frame(&app->gfx.frame);
	world_step_dense(&app->world);
	draw_world_to_frame(&app->world, &app->view, &app->gfx.frame);
	mlx_put_image_to_window(app->gfx.mlx, app->gfx.win, app->gfx.frame.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	if (!envp || !*envp || argc != 1)
		return (1);
	(void)argv;
	ft_bzero(&app, sizeof(app));
	if (!app_init(&app))
		return (app_destroy(&app, 1), 1);
	mlx_hook(app.gfx.win, 2, 1L << 0, key_pressed, &app);
	mlx_hook(app.gfx.win, 17, 1L << 17, on_close, &app);
	mlx_loop_hook(app.gfx.mlx, loop_hook, &app);
	mlx_loop(app.gfx.mlx);
	return (app_destroy(&app, 0), 0);
}
