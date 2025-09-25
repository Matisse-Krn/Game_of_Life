#include "GoL.h"

static void	help_line_text(int line_idx, char *out, int cap)
{
	buf_reset(out);
	if (line_idx == 0)
	{
		buf_cat_str(out, cap, "pause/play: [SPACE]");
		buf_cat_sep(out, cap);
		buf_cat_str(out, cap, "step: [N]");
		buf_cat_sep(out, cap);
		buf_cat_str(out, cap, "TPS: [PgUp/PgDn]");
		buf_cat_sep(out, cap);
		buf_cat_str(out, cap, "zoom: [+/-]");
		buf_cat_sep(out, cap);
		buf_cat_str(out, cap, "HUD: [H]");
		return ;
	}
	buf_cat_str(out, cap, "pan: [ARROWS]");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "border mode: [B]");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "clear: [C]");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "reseed: [R]");
	buf_cat_sep(out, cap);
	buf_cat_str(out, cap, "quit: [ESC]");
}

static int	help_panel_max_width(t_app *app)
{
	char	line[160];
	int		i;
	int		max_w;
	int		w;

	max_w = 0;
	i = 0;
	while (i < 2)
	{
		help_line_text(i, line, (int) sizeof(line));
		w = text_measure_width(app->ui_font, line,
				HUD_TEXT_SIZE, HUD_TEXT_SIZE);
		if (w > max_w)
			max_w = w;
		i = i + 1;
	}
	return (max_w);
}

static void	help_panel_draw_lines(t_app *app, t_rect box, int step)
{
	char		line[160];
	int			i;
	t_textdraw	td;

	i = 0;
	while (i < 2)
	{
		help_line_text(i, line, (int) sizeof(line));
		td.img = &app->gfx.frame;
		td.font = app->ui_font;
		td.str = line;
		td.pos.x = box.x + HUD_PADDING_PX;
		td.pos.y = box.y + HUD_PADDING_PX + i * step;
		td.fmt.size = HUD_TEXT_SIZE;
		td.fmt.spacing = HUD_TEXT_SIZE;
		td.fmt.color = HUD_COLOR_TEXT;
		text_draw(&td);
		i = i + 1;
	}
}

void	draw_help_panel(t_app *app)
{
	t_rect	box;
	int		step;
	int		max_w;

	step = hud_line_step();
	max_w = help_panel_max_width(app);
	box.w = max_w + 2 * HUD_PADDING_PX;
	box.h = 2 * text_line_height(HUD_TEXT_SIZE)
		+ 2 * HUD_PADDING_PX + HUD_LINE_GAP_PX;
	box.x = HUD_MARGIN_PX;
	box.y = app->gfx.win_h - HUD_MARGIN_PX - box.h;
	panel_draw_box(&app->gfx.frame, box, HUD_COLOR_BG, HUD_COLOR_BORDER);
	help_panel_draw_lines(app, box, step);
}
