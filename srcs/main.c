#include "GoL.h"

static void	app_destroy(t_app *app)
{
	if (!app)
		return ;
	if ((app->init_status & INIT_IMG) && app->gfx.frame.img)
	{
		mlx_destroy_image(app->gfx.mlx, app->gfx.frame.img);
		app->gfx.frame.img = NULL;
		app->init_status &= ~INIT_IMG;
	}
	if ((app->init_status & INIT_WIN) && app->gfx.win)
	{
		mlx_destroy_window(app->gfx.mlx, app->gfx.win);
		app->gfx.win = NULL;
		app->init_status &= ~INIT_WIN;
	}
	if ((app->init_status & INIT_MLX) && app->gfx.mlx)
	{
		mlx_destroy_display(app->gfx.mlx);
		free(app->gfx.mlx);
		app->gfx.mlx = NULL;
		app->init_status &= ~ INIT_MLX;
	}
}

static int	init_mlx_image(t_app *app)
{
	app->gfx.frame.img = mlx_new_image(app->gfx.mlx, app->gfx.win_w, app->gfx.win_h);
	if (!app->gfx.frame.img)
		return (FALSE);
	app->init_status |= INIT_IMG;
	

	app->gfx.frame.addr = mlx_get_data_addr(app->gfx.frame.img, &app->gfx.frame.bpp, &app->gfx.frame.ll, &app->gfx.frame.endian);
	if (!app->gfx.frame.addr || app->gfx.frame.bpp != 32 || app->gfx.frame.ll <= 0)
		return (FALSE);
	app->gfx.frame.w = app->gfx.win_w;
	app->gfx.frame.h = app->gfx.win_h;
	

	return (TRUE);
}

static int	init_mlx_basics(t_app *app)
{
	app->gfx.mlx = mlx_init();
	if (!app->gfx.mlx)
		return (FALSE);
	app->init_status |= INIT_MLX;
	

	mlx_get_screen_size(app->gfx.mlx, &app->gfx.win_w, &app->gfx.win_h);
	app->gfx.win = mlx_new_window(app->gfx.mlx, app->gfx.win_w, app->gfx.win_h, "GoL - Game of Life");
	if (!app->gfx.win)
		return (FALSE);
	app->init_status |= INIT_WIN;
	

	return (TRUE);
}

static int	app_init(t_app *app)
{
	app->init_status = INIT_NONE;
	if (!init_mlx_basics(app) || !init_mlx_image(app))
		return (FALSE);
	return (TRUE);

}

int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	if (!envp || !*envp || argc != 1)
		return (1);
	(void)argv;
	ft_bzero(&app, sizeof(app));
	if (!app_init(&app))
		return (app_destroy(&app), FALSE);
	return (app_destroy(&app), 0);
}
