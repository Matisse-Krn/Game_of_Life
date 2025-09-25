#include "GoL.h"

static int	mouse_compute_cell_coords(const t_app *app, int *cx, int *cy)
{
	int	cell_px_safe;

	cell_px_safe = app->view.cell_px;
	if (cell_px_safe < 1)
		cell_px_safe = 1;
	*cx = app->view.offset_x;
	*cy = app->view.offset_y;
	if (app->in.mouse_last_x >= 0)
		*cx = *cx + (app->in.mouse_last_x / cell_px_safe);
	if (app->in.mouse_last_y >= 0)
		*cy = *cy + (app->in.mouse_last_y / cell_px_safe);
	if (*cx < 0 || *cy < 0 || *cx >= app->world.w || *cy >= app->world.h)
		return (0);
	return (1);
}

static void	mouse_line_text(t_app *app, char *out, int cap)
{
	int	cx;
	int	cy;
	int	alive;

	buf_reset(out);
	if (!mouse_compute_cell_coords(app, &cx, &cy))
	{
		buf_cat_str(out, cap, "CUR off-grid");
		return ;
	}
	alive = 0;
	if (app->world.cur[cy * app->world.w + cx] != 0)
		alive = 1;
	buf_cat_str(out, cap, "CUR X=");
	buf_cat_i32(out, cap, cx);
	buf_cat_str(out, cap, " Y=");
	buf_cat_i32(out, cap, cy);
	buf_cat_sep(out, cap);
	if (alive)
		buf_cat_str(out, cap, "ALIVE");
	else
		buf_cat_str(out, cap, "DEAD");
}

static void	draw_mouse_panel(t_app *app)
{
	char	line[128];
	int		w;
	int		h;
	t_rect	box;

	mouse_line_text(app, line, (int) sizeof(line));
	w = text_measure_width(app->ui_font, line,
			HUD_TEXT_SIZE, HUD_TEXT_SIZE);
	h = text_line_height(HUD_TEXT_SIZE);
	box.w = w + 2 * HUD_PADDING_PX;
	box.h = h + 2 * HUD_PADDING_PX;
	box.x = app->gfx.win_w - HUD_MARGIN_PX - box.w;
	box.y = HUD_MARGIN_PX;
	panel_draw_box(&app->gfx.frame, box, HUD_COLOR_BG, HUD_COLOR_BORDER);
	text_draw(&(t_textdraw){&app->gfx.frame, app->ui_font, line,
		(t_point){box.x + HUD_PADDING_PX, box.y + HUD_PADDING_PX},
		(t_textfmt){HUD_TEXT_SIZE, HUD_TEXT_SIZE,
		HUD_COLOR_TEXT}});
}

void	hud_draw(t_app *app)
{
	if (!app || !app->ui_font || !app->hud_visible)
		return ;
	draw_status_panel(app);
	draw_mouse_panel(app);
	draw_help_panel(app);
}
