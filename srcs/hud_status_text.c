#include "GoL.h"

static void	status_line0_text(t_app *app, char *out, int cap)
{
	buf_reset(out);
	if (app->run == RUN_PLAY)
		buf_cat_str(out, cap, "PLAY");
	else
		buf_cat_str(out, cap, "PAUSED");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "GEN ");
	buf_cat_u32(out, cap, app->world.gen);
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "TPS ");
	buf_cat_f1(out, cap, app->clk.target_tps);
}

static void	status_line1_text(t_app *app, char *out, int cap)
{
	unsigned int	cells_total;
	double			pct;

	buf_reset(out);
	cells_total = (unsigned int)(app->world.w * app->world.h);
	pct = 0.0;
	if (cells_total != 0)
		pct = 100.0 * (double)app->world.population / (double)cells_total;
	buf_cat_str(out, cap, "POP ");
	buf_cat_u32(out, cap, app->world.population);
	buf_cat_str(out, cap, " (");
	buf_cat_f1(out, cap, pct);
	buf_cat_str(out, cap, "%)");
	buf_cat_sep(out, cap);
	if (app->world.border == BORDER_TORE)
		buf_cat_str(out, cap, "TORE");
	else
		buf_cat_str(out, cap, "CLAMP");
}

static void	status_line2_text(t_app *app, char *out, int cap)
{
	int	vis_w;
	int	vis_h;

	buf_reset(out);
	vis_w = 0;
	vis_h = 0;
	if (app->view.cell_px > 0)
		vis_w = app->gfx.win_w / app->view.cell_px;
	if (app->view.cell_px > 0)
		vis_h = app->gfx.win_h / app->view.cell_px;
	buf_cat_str(out, cap, "Cell size ");
	buf_cat_i32(out, cap, app->view.cell_px);
	buf_cat_str(out, cap, "px");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "Area ");
	buf_cat_i32(out, cap, vis_w);
	buf_cat_char(out, cap, 'x');
	buf_cat_i32(out, cap, vis_h);
}

void	status_line_text(t_app *app, int line_idx, char *out, int cap)
{
	if (line_idx == 0)
	{
		status_line0_text(app, out, cap);
		return ;
	}
	if (line_idx == 1)
	{
		status_line1_text(app, out, cap);
		return ;
	}
	status_line2_text(app, out, cap);
}
