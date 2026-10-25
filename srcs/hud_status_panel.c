#include "GoL.h"

static unsigned int	status_line_color(const t_app *app, int index)
{
	if (index != 0)
		return (HUD_COLOR_TEXT);
	if (app->run == RUN_PLAY)
		return (HUD_COLOR_ACCENT_PLAY);
	return (HUD_COLOR_ACCENT_PAUSE);
}

static int	status_panel_max_width(t_app *app, int size)
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
		w = text_measure_width(app->ui_font, line, size, size);
		if (w > max_w)
			max_w = w;
		i = i + 1;
	}
	return (max_w);
}

static int	status_panel_text_size(t_app *app)
{
	int	available;

	available = app->gfx.win_w - 2 * (HUD_MARGIN_PX + HUD_PADDING_PX);
	if (available <= 0)
		return (0);
	if (status_panel_max_width(app, HUD_TEXT_SIZE) <= available)
		return (HUD_TEXT_SIZE);
	if (status_panel_max_width(app, 1) <= available)
		return (1);
	return (0);
}

t_rect	hud_status_panel_rect(t_app *app)
{
	t_rect	box;
	int		size;

	box = (t_rect){0};
	if (!app || !app->ui_font)
		return (box);
	size = status_panel_text_size(app);
	if (!size)
		return (box);
	box.x = HUD_MARGIN_PX;
	box.y = HUD_MARGIN_PX;
	box.w = status_panel_max_width(app, size) + 2 * HUD_PADDING_PX;
	box.h = 3 * text_line_height(size)
		+ 2 * HUD_PADDING_PX + 2 * HUD_LINE_GAP_PX;
	if (box.h + 2 * HUD_MARGIN_PX > app->gfx.win_h)
		return ((t_rect){0});
	return (box);
}

static void	status_panel_draw_lines(t_app *app, t_rect box, int step,
	int size)
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
		td.fmt.size = size;
		td.fmt.spacing = size;
		td.fmt.color = status_line_color(app, i);
		text_draw(&td);
		i = i + 1;
	}
}

void	draw_status_panel(t_app *app)
{
	t_rect	box;
	int		step;
	int		size;

	box = hud_status_panel_rect(app);
	if (box.w <= 0)
		return ;
	size = status_panel_text_size(app);
	step = text_line_height(size) + HUD_LINE_GAP_PX;
	panel_draw_box(&app->gfx.frame, box, HUD_COLOR_BG, HUD_COLOR_BORDER);
	status_panel_draw_lines(app, box, step, size);
}
