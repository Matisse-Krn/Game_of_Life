#include "font5.h"

void	install_digits_0_9(t_font *f)
{
	font_install_glyph(f, '0',
		(t_glyph5){{ROW_01110, ROW_10011, ROW_10101, ROW_11001, ROW_01110}});
	font_install_glyph(f, '1',
		(t_glyph5){{ROW_00100, ROW_01100, ROW_00100, ROW_00100, ROW_01110}});
	font_install_glyph(f, '2',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_00110, ROW_01000, ROW_11111}});
	font_install_glyph(f, '3',
		(t_glyph5){{ROW_11110, ROW_00001, ROW_00110, ROW_00001, ROW_11110}});
	font_install_glyph(f, '4',
		(t_glyph5){{ROW_10010, ROW_10010, ROW_11111, ROW_00010, ROW_00010}});
	font_install_glyph(f, '5',
		(t_glyph5){{ROW_11111, ROW_10000, ROW_11110, ROW_00001, ROW_11110}});
	font_install_glyph(f, '6',
		(t_glyph5){{ROW_01110, ROW_10000, ROW_11110, ROW_10001, ROW_01110}});
	font_install_glyph(f, '7',
		(t_glyph5){{ROW_11111, ROW_00001, ROW_00010, ROW_00100, ROW_00100}});
	font_install_glyph(f, '8',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_01110, ROW_10001, ROW_01110}});
	font_install_glyph(f, '9',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_01111, ROW_00001, ROW_01110}});
}

void	install_uppercase_a_l(t_font *f)
{
	font_install_glyph(f, 'A',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_11111, ROW_10001, ROW_10001}});
	font_install_glyph(f, 'B',
		(t_glyph5){{ROW_11110, ROW_10001, ROW_11110, ROW_10001, ROW_11110}});
	font_install_glyph(f, 'C',
		(t_glyph5){{ROW_01111, ROW_10000, ROW_10000, ROW_10000, ROW_01111}});
	font_install_glyph(f, 'D',
		(t_glyph5){{ROW_11110, ROW_10001, ROW_10001, ROW_10001, ROW_11110}});
	font_install_glyph(f, 'E',
		(t_glyph5){{ROW_11111, ROW_10000, ROW_11110, ROW_10000, ROW_11111}});
	font_install_glyph(f, 'F',
		(t_glyph5){{ROW_11111, ROW_10000, ROW_11110, ROW_10000, ROW_10000}});
	font_install_glyph(f, 'G',
		(t_glyph5){{ROW_01111, ROW_10000, ROW_10111, ROW_10001, ROW_01111}});
	font_install_glyph(f, 'H',
		(t_glyph5){{ROW_10001, ROW_10001, ROW_11111, ROW_10001, ROW_10001}});
	font_install_glyph(f, 'I',
		(t_glyph5){{ROW_01110, ROW_00100, ROW_00100, ROW_00100, ROW_01110}});
	font_install_glyph(f, 'J',
		(t_glyph5){{ROW_00001, ROW_00001, ROW_00001, ROW_10001, ROW_01110}});
	font_install_glyph(f, 'K',
		(t_glyph5){{ROW_10001, ROW_10010, ROW_11100, ROW_10010, ROW_10001}});
	font_install_glyph(f, 'L',
		(t_glyph5){{ROW_10000, ROW_10000, ROW_10000, ROW_10000, ROW_11111}});
}

void	install_uppercase_m_x(t_font *f)
{
	font_install_glyph(f, 'M',
		(t_glyph5){{ROW_10001, ROW_11011, ROW_10101, ROW_10001, ROW_10001}});
	font_install_glyph(f, 'N',
		(t_glyph5){{ROW_10001, ROW_11001, ROW_10101, ROW_10011, ROW_10001}});
	font_install_glyph(f, 'O',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_10001, ROW_10001, ROW_01110}});
	font_install_glyph(f, 'P',
		(t_glyph5){{ROW_11110, ROW_10001, ROW_11110, ROW_10000, ROW_10000}});
	font_install_glyph(f, 'Q',
		(t_glyph5){{ROW_01110, ROW_10001, ROW_10001, ROW_10011, ROW_01111}});
	font_install_glyph(f, 'R',
		(t_glyph5){{ROW_11110, ROW_10001, ROW_11110, ROW_10010, ROW_10001}});
	font_install_glyph(f, 'S',
		(t_glyph5){{ROW_01111, ROW_10000, ROW_01110, ROW_00001, ROW_11110}});
	font_install_glyph(f, 'T',
		(t_glyph5){{ROW_11111, ROW_00100, ROW_00100, ROW_00100, ROW_00100}});
	font_install_glyph(f, 'U',
		(t_glyph5){{ROW_10001, ROW_10001, ROW_10001, ROW_10001, ROW_01110}});
	font_install_glyph(f, 'V',
		(t_glyph5){{ROW_10001, ROW_10001, ROW_10001, ROW_01010, ROW_00100}});
	font_install_glyph(f, 'W',
		(t_glyph5){{ROW_10001, ROW_10001, ROW_10101, ROW_11011, ROW_10001}});
	font_install_glyph(f, 'X',
		(t_glyph5){{ROW_10001, ROW_01010, ROW_00100, ROW_01010, ROW_10001}});
}

void	install_uppercase_y_z(t_font *f)
{
	font_install_glyph(f, 'Y',
		(t_glyph5){{ROW_10001, ROW_01010, ROW_00100, ROW_00100, ROW_00100}});
	font_install_glyph(f, 'Z',
		(t_glyph5){{ROW_11111, ROW_00010, ROW_00100, ROW_01000, ROW_11111}});
}
