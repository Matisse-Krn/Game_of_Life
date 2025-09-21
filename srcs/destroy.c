#include "GoL.h"

void	app_destroy(t_app *app)
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
