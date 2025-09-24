#include "GoL.h"

int	on_close(t_app *app)
{
	app_destroy(app, 0);
	return (0);
}

static void	world_free(t_world *world)
{
	if (!world)
		return ;
	if (world->cur)
		free(world->cur);
	if (world->next)
		free(world->next);
	ft_bzero(world, sizeof(*world));
}

static void	mlx_destroy(t_app *app)
{
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
		app->init_status &= ~INIT_MLX;
	}
}

int	app_destroy(t_app *app, int exit_code)
{
	if (!app)
		exit(exit_code);
	if ((app->init_status & INIT_FONT) && app->ui_font)
	{
		font_destroy(&app->ui_font);
		app->ui_font = NULL;
		app->init_status &= ~INIT_FONT;
	}
	if ((app->init_status & INIT_WORLD))
	{
		world_free(&app->world);
		app->init_status &= ~INIT_WORLD;
	}
	mlx_destroy(app);
	exit(exit_code);
}
