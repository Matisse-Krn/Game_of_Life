#include "GoL.h"

void	buf_cat_f1(char *dst, int cap, double x)
{
	int	scaled;
	int	ip;
	int	fp;

	if (x >= 0.0)
		scaled = (int)(x * 10.0 + 0.5);
	else
		scaled = (int)(x * 10.0 - 0.5);
	ip = scaled / 10;
	fp = scaled % 10;
	if (fp < 0)
		fp = -fp;
	buf_cat_i32(dst, cap, ip);
	buf_cat_char(dst, cap, '.');
	buf_cat_char(dst, cap, (char)('0' + fp));
}

void	buf_cat_sep(char *dst, int cap)
{
	buf_cat_str(dst, cap, "  |  ");
}

int	hud_line_step(void)
{
	int	line_h;

	line_h = text_line_height(HUD_TEXT_SIZE);
	return (line_h + HUD_LINE_GAP_PX);
}

void	panel_draw_box(t_img *dst, t_rect box, int bg, int border)
{
	t_rect	edge;

	fill_rect_safe(dst, box, bg);
	edge.x = box.x;
	edge.y = box.y;
	edge.w = box.w;
	edge.h = 1;
	fill_rect_safe(dst, edge, border);
	edge.x = box.x;
	edge.y = box.y + box.h - 1;
	edge.w = box.w;
	edge.h = 1;
	fill_rect_safe(dst, edge, border);
	edge.x = box.x;
	edge.y = box.y;
	edge.w = 1;
	edge.h = box.h;
	fill_rect_safe(dst, edge, border);
	edge.x = box.x + box.w - 1;
	edge.y = box.y;
	edge.w = 1;
	edge.h = box.h;
	fill_rect_safe(dst, edge, border);
}
