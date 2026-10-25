#include "GoL.h"

static void	help_line_text(int line_idx, char *out, int cap, int compact)
{
	buf_reset(out);
	if (compact)
	{
		if (line_idx == 0)
			buf_cat_str(out, cap, "H HUD SPACE PAUSE");
		else
			buf_cat_str(out, cap, "ESC QUIT N STEP");
		return ;
	}
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

static int	help_panel_max_width(t_app *app, int size, int compact)
{
	char	line[160];
	int		i;
	int		max_w;
	int		w;

	max_w = 0;
	i = 0;
	while (i < 2)
	{
		help_line_text(i, line, (int) sizeof(line), compact);
		w = text_measure_width(app->ui_font, line, size, size);
		if (w > max_w)
			max_w = w;
		i = i + 1;
	}
	return (max_w);
}

static int	help_panel_text_size(t_app *app, int *compact)
{
	int	available;

	*compact = 0;
	available = app->gfx.win_w - 2 * (HUD_MARGIN_PX + HUD_PADDING_PX);
	if (available <= 0)
		return (0);
	if (help_panel_max_width(app, HUD_TEXT_SIZE, 0) <= available)
		return (HUD_TEXT_SIZE);
	if (help_panel_max_width(app, 1, 0) <= available)
		return (1);
	*compact = 1;
	if (help_panel_max_width(app, 1, 1) <= available)
		return (1);
	return (0);
}

static void	help_panel_draw_lines(t_app *app, t_rect box, int step,
	int size, int compact)
{
	char		line[160];
	int			i;
	t_textdraw	td;

	i = 0;
	while (i < 2)
	{
		help_line_text(i, line, (int) sizeof(line), compact);
		td.img = &app->gfx.frame;
		td.font = app->ui_font;
		td.str = line;
		td.pos.x = box.x + HUD_PADDING_PX;
		td.pos.y = box.y + HUD_PADDING_PX + i * step;
		td.fmt.size = size;
		td.fmt.spacing = size;
		td.fmt.color = HUD_COLOR_TEXT;
		text_draw(&td);
		i = i + 1;
	}
}

void	draw_help_panel(t_app *app)
{
	t_rect	box;
	t_rect	status;
	int		step;
	int		size;
	int		compact;

	size = help_panel_text_size(app, &compact);
	if (!size)
		return ;
	step = text_line_height(size) + HUD_LINE_GAP_PX;
	box.w = help_panel_max_width(app, size, compact) + 2 * HUD_PADDING_PX;
	box.h = 2 * text_line_height(size)
		+ 2 * HUD_PADDING_PX + HUD_LINE_GAP_PX;
	box.x = HUD_MARGIN_PX;
	box.y = app->gfx.win_h - HUD_MARGIN_PX - box.h;
	if (box.y < HUD_MARGIN_PX)
		return ;
	status = hud_status_panel_rect(app);
	if (status.w > 0 && box.y < status.y + status.h + HUD_MARGIN_PX)
		return ;
	panel_draw_box(&app->gfx.frame, box, HUD_COLOR_BG, HUD_COLOR_BORDER);
	help_panel_draw_lines(app, box, step, size, compact);
}
