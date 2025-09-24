#include "font5.h"

#define ROW(b4,b3,b2,b1,b0) \
	((uint8_t)(((b4)<<7)|((b3)<<6)|((b2)<<5)|((b1)<<4)|((b0)<<3)))
#define GLY5(r0,r1,r2,r3,r4) (t_glyph5){{(r0),(r1),(r2),(r3),(r4)}}

static void	install_basic(t_font *f)
{
	t_glyph5	space;
	t_glyph5	qmark;

	space = GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0),
			ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0));
	qmark = GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1), ROW(0, 0, 0, 1, 0),
			ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0));
	font_install_glyph(f, ' ', space);
	font_install_glyph(f, '?', qmark);
}

static void	install_punct_basic(t_font *f)
{
	font_install_glyph(f, ':', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, '.', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0),
			ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, ',', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0),
			ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0)));
	font_install_glyph(f, ';', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0)));
	font_install_glyph(f, '!', GLY5(ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, '\\', GLY5(ROW(1, 0, 0, 0, 0), ROW(0, 1, 0, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 1, 0), ROW(0, 0, 0, 0, 1)));
	font_install_glyph(f, '|', GLY5(ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0)));
}

static void	install_punct_ops(t_font *f)
{
	font_install_glyph(f, '-', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0),
			ROW(0, 1, 1, 1, 0), ROW(0, 0, 0, 0, 0), ROW(0, 0, 0, 0, 0)));
	font_install_glyph(f, '+', GLY5(ROW(0, 0, 0, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 1, 1, 1, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 0, 0)));
	font_install_glyph(f, '/', GLY5(ROW(0, 0, 0, 0, 1), ROW(0, 0, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0), ROW(1, 0, 0, 0, 0)));
	font_install_glyph(f, '%', GLY5(ROW(1, 0, 0, 0, 1), ROW(0, 0, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, '=', GLY5(ROW(0, 0, 0, 0, 0), ROW(1, 1, 1, 1, 1),
			ROW(0, 0, 0, 0, 0), ROW(1, 1, 1, 1, 1), ROW(0, 0, 0, 0, 0)));
}

static void	install_punct_brackets(t_font *f)
{
	font_install_glyph(f, '[', GLY5(ROW(0, 0, 1, 1, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 1, 0)));
	font_install_glyph(f, ']', GLY5(ROW(0, 1, 1, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 1, 0, 0)));
	font_install_glyph(f, '(', GLY5(ROW(0, 0, 0, 1, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 1, 0)));
	font_install_glyph(f, ')', GLY5(ROW(0, 1, 0, 0, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0)));
	font_install_glyph(f, '<', GLY5(ROW(1, 0, 0, 0, 0), ROW(0, 1, 0, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0), ROW(1, 0, 0, 0, 0)));
	font_install_glyph(f, '>', GLY5(ROW(0, 0, 0, 0, 1), ROW(0, 0, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 0, 1, 0), ROW(0, 0, 0, 0, 1)));
}

void	font5_install_defaults(t_font *f)
{
	if (!f)
		return ;
	install_basic(f);
	install_digits_0_9(f);
	install_uppercase_a_l(f);
	install_uppercase_m_x(f);
	install_uppercase_y_z(f);
	install_punct_basic(f);
	install_punct_ops(f);
	install_punct_brackets(f);
}
