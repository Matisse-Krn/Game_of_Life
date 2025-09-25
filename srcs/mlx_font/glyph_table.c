#include "font5.h"

static void	install_basic(t_font *f)
{
	t_glyph5	space;
	t_glyph5	qmark;

	space = (t_glyph5){{ROW_00000, ROW_00000, ROW_00000,
		ROW_00000, ROW_00000}};
	qmark = (t_glyph5){{ROW_01110, ROW_10001, ROW_00010,
		ROW_00000, ROW_00100}};
	font_install_glyph(f, ' ', space);
	font_install_glyph(f, '?', qmark);
}

static void	install_punct_basic(t_font *f)
{
	font_install_glyph(f, ':',
		(t_glyph5){{ROW_00000, ROW_00100, ROW_00000, ROW_00100, ROW_00000}});
	font_install_glyph(f, '.',
		(t_glyph5){{ROW_00000, ROW_00000, ROW_00000, ROW_00000, ROW_00100}});
	font_install_glyph(f, ',',
		(t_glyph5){{ROW_00000, ROW_00000, ROW_00000, ROW_00100, ROW_01000}});
	font_install_glyph(f, ';',
		(t_glyph5){{ROW_00000, ROW_00100, ROW_00000, ROW_00100, ROW_01000}});
	font_install_glyph(f, '!',
		(t_glyph5){{ROW_00100, ROW_00100, ROW_00100, ROW_00000, ROW_00100}});
	font_install_glyph(f, '\\',
		(t_glyph5){{ROW_10000, ROW_01000, ROW_00100, ROW_00010, ROW_00001}});
	font_install_glyph(f, '|',
		(t_glyph5){{ROW_00100, ROW_00100, ROW_00100, ROW_00100, ROW_00100}});
}

static void	install_punct_ops(t_font *f)
{
	font_install_glyph(f, '-',
		(t_glyph5){{ROW_00000, ROW_00000, ROW_01110, ROW_00000, ROW_00000}});
	font_install_glyph(f, '+',
		(t_glyph5){{ROW_00000, ROW_00100, ROW_01110, ROW_00100, ROW_00000}});
	font_install_glyph(f, '/',
		(t_glyph5){{ROW_00001, ROW_00010, ROW_00100, ROW_01000, ROW_10000}});
	font_install_glyph(f, '%',
		(t_glyph5){{ROW_10001, ROW_00010, ROW_00100, ROW_01000, ROW_10001}});
	font_install_glyph(f, '=',
		(t_glyph5){{ROW_00000, ROW_11111, ROW_00000, ROW_11111, ROW_00000}});
}

static void	install_punct_brackets(t_font *f)
{
	font_install_glyph(f, '[',
		(t_glyph5){{ROW_00110, ROW_00100, ROW_00100, ROW_00100, ROW_00110}});
	font_install_glyph(f, ']',
		(t_glyph5){{ROW_01100, ROW_00100, ROW_00100, ROW_00100, ROW_01100}});
	font_install_glyph(f, '(',
		(t_glyph5){{ROW_00010, ROW_00100, ROW_00100, ROW_00100, ROW_00010}});
	font_install_glyph(f, ')',
		(t_glyph5){{ROW_01000, ROW_00100, ROW_00100, ROW_00100, ROW_01000}});
	font_install_glyph(f, '<',
		(t_glyph5){{ROW_10000, ROW_01000, ROW_00100, ROW_01000, ROW_10000}});
	font_install_glyph(f, '>',
		(t_glyph5){{ROW_00001, ROW_00010, ROW_00100, ROW_00010, ROW_00001}});
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
