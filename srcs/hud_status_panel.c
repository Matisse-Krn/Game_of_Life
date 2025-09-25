#include "GoL.h"

static unsigned int	status_line_color(const t_app *app, int index)
{
	if (index != 0)
		return (HUD_COLOR_TEXT);
	if (app->run == RUN_PLAY)
		return (HUD_COLOR_ACCENT_PLAY);
	return (HUD_COLOR_ACCENT_PAUSE);
}

static int	status_panel_max_width(t_app *app)
{
	char	line[128];
	int		i;
	int		max_w;
	int		w;

	max_w = 0;
	i = 0;
	while (i < 3)
	{
		status_line_text(app, i, line, (int) sizeof(line));
		w = text_measure_width(app->ui_font, line,
				HUD_TEXT_SIZE, HUD_TEXT_SIZE);
		if (w > max_w)
			max_w = w;
		i = i + 1;
	}
	return (max_w);
}

static void	status_panel_draw_lines(t_app *app, t_rect box, int step)
{
	char		line[128];
	int			i;
	t_textdraw	td;

	i = 0;
	while (i < 3)
	{
		status_line_text(app, i, line, (int) sizeof(line));
		td.img = &app->gfx.frame;
		td.font = app->ui_font;
		td.str = line;
		td.pos.x = box.x + HUD_PADDING_PX;
		td.pos.y = box.y + HUD_PADDING_PX + i * step;
		td.fmt.size = HUD_TEXT_SIZE;
		td.fmt.spacing = HUD_TEXT_SIZE;
		td.fmt.color = status_line_color(app, i);
		text_draw(&td);
		i = i + 1;
	}
}

void	draw_status_panel(t_app *app)
{
	t_rect	box;
	int		step;
	int		max_w;

	step = hud_line_step();
	max_w = status_panel_max_width(app);
	box.x = HUD_MARGIN_PX;
	box.y = HUD_MARGIN_PX;
	box.w = max_w + 2 * HUD_PADDING_PX;
	box.h = 3 * text_line_height(HUD_TEXT_SIZE)
		+ 2 * HUD_PADDING_PX + 2 * HUD_LINE_GAP_PX;
	panel_draw_box(&app->gfx.frame, box, HUD_COLOR_BG, HUD_COLOR_BORDER);
	status_panel_draw_lines(app, box, step);
}
