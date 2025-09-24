#include "font5.h"

static unsigned char	map_char(const t_font *f, unsigned char ch)
{
	unsigned char	up;

	if (f->has_glyph[ch])
		return (ch);
	if (ch >= 'a' && ch <= 'z')
	{
		up = (unsigned char)(ch - 'a' + 'A');
		if (f->has_glyph[up])
			return (up);
	}
	return (f->fallback);
}

static int	bit_on(uint8_t row, int col)
{
	uint8_t	mask;

	mask = (uint8_t)(0x80u >> col);
	return ((row & mask) != 0);
}

static void	draw_glyph5(t_img *img, const t_glyph5 *g,
				t_point pos, t_textfmt fmt)
{
	int		r;
	int		c;
	t_rect	rc;

	r = 0;
	while (r < FONT5_ROWS)
	{
		c = 0;
		while (c < FONT5_COLS)
		{
			if (bit_on(g->rows[r], c))
			{
				rc.x = pos.x + c * fmt.size;
				rc.y = pos.y + r * fmt.size;
				rc.w = fmt.size;
				rc.h = fmt.size;
				fill_rect_safe(img, rc, fmt.color);
			}
			c++;
		}
		r++;
	}
}

void	text_draw(const t_textdraw *td)
{
	int		i;
	int		x;
	int		char_w;
	int		spacing;
	t_point	pos;

	if (!td || !td->img || !td->font || !td->str || td->fmt.size <= 0)
		return ;
	spacing = td->fmt.spacing;
	if (spacing < 0)
		spacing = 0;
	char_w = FONT5_COLS * td->fmt.size;
	x = td->pos.x;
	i = 0;
	while (td->str[i])
	{
		pos.x = x;
		pos.y = td->pos.y;
		draw_glyph5(td->img, &td->font->glyphs[map_char(td->font,
				(unsigned char)td->str[i])], pos, td->fmt);
		x += char_w;
		if (td->str[i + 1])
			x += spacing;
		i++;
	}
}

void	text_draw_centered(const t_textcenter *tc)
{
	int			w;
	int			h;
	t_textdraw	td;
	t_point		pos;

	if (!tc || !tc->img || !tc->font || !tc->str || tc->fmt.size <= 0)
		return ;
	w = text_measure_width(tc->font, tc->str, tc->fmt.size, tc->fmt.spacing);
	h = text_line_height(tc->fmt.size);
	pos.x = tc->frame.x + (tc->frame.w - w) / 2;
	pos.y = tc->frame.y + (tc->frame.h - h) / 2;
	td.img = tc->img;
	td.font = tc->font;
	td.str = tc->str;
	td.pos = pos;
	td.fmt = tc->fmt;
	text_draw(&td);
}
