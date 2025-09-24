#include "font5.h"

#define ROW(b4,b3,b2,b1,b0) \
	((uint8_t)(((b4)<<7)|((b3)<<6)|((b2)<<5)|((b1)<<4)|((b0)<<3)))
#define GLY5(r0,r1,r2,r3,r4) (t_glyph5){{(r0),(r1),(r2),(r3),(r4)}}

void	install_digits_0_9(t_font *f)
{
	font_install_glyph(f, '0', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 1, 1),
			ROW(1, 0, 1, 0, 1), ROW(1, 1, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, '1', GLY5(ROW(0, 0, 1, 0, 0), ROW(0, 1, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, '2', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(0, 0, 1, 1, 0), ROW(0, 1, 0, 0, 0), ROW(1, 1, 1, 1, 1)));
	font_install_glyph(f, '3', GLY5(ROW(1, 1, 1, 1, 0), ROW(0, 0, 0, 0, 1),
			ROW(0, 0, 1, 1, 0), ROW(0, 0, 0, 0, 1), ROW(1, 1, 1, 1, 0)));
	font_install_glyph(f, '4', GLY5(ROW(1, 0, 0, 1, 0), ROW(1, 0, 0, 1, 0),
			ROW(1, 1, 1, 1, 1), ROW(0, 0, 0, 1, 0), ROW(0, 0, 0, 1, 0)));
	font_install_glyph(f, '5', GLY5(ROW(1, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(1, 1, 1, 1, 0), ROW(0, 0, 0, 0, 1), ROW(1, 1, 1, 1, 0)));
	font_install_glyph(f, '6', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 0),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, '7', GLY5(ROW(1, 1, 1, 1, 1), ROW(0, 0, 0, 0, 1),
			ROW(0, 0, 0, 1, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, '8', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, '9', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(0, 1, 1, 1, 1), ROW(0, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
}

void	install_uppercase_a_l(t_font *f)
{
	font_install_glyph(f, 'A', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 1, 1, 1, 1), ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'B', GLY5(ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1), ROW(1, 1, 1, 1, 0)));
	font_install_glyph(f, 'C', GLY5(ROW(0, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(1, 0, 0, 0, 0), ROW(1, 0, 0, 0, 0), ROW(0, 1, 1, 1, 1)));
	font_install_glyph(f, 'D', GLY5(ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1), ROW(1, 1, 1, 1, 0)));
	font_install_glyph(f, 'E', GLY5(ROW(1, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 0), ROW(1, 1, 1, 1, 1)));
	font_install_glyph(f, 'F', GLY5(ROW(1, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 0), ROW(1, 0, 0, 0, 0)));
	font_install_glyph(f, 'G', GLY5(ROW(0, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(1, 0, 1, 1, 1), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 1)));
	font_install_glyph(f, 'H', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1),
			ROW(1, 1, 1, 1, 1), ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'I', GLY5(ROW(0, 1, 1, 1, 0), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, 'J', GLY5(ROW(0, 0, 0, 0, 1), ROW(0, 0, 0, 0, 1),
			ROW(0, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, 'K', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 1, 0),
			ROW(1, 1, 1, 0, 0), ROW(1, 0, 0, 1, 0), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'L', GLY5(ROW(1, 0, 0, 0, 0), ROW(1, 0, 0, 0, 0),
			ROW(1, 0, 0, 0, 0), ROW(1, 0, 0, 0, 0), ROW(1, 1, 1, 1, 1)));
}

void	install_uppercase_m_x(t_font *f)
{
	font_install_glyph(f, 'M', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 1, 0, 1, 1),
			ROW(1, 0, 1, 0, 1), ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'N', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 1, 0, 0, 1),
			ROW(1, 0, 1, 0, 1), ROW(1, 0, 0, 1, 1), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'O', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, 'P', GLY5(ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 0), ROW(1, 0, 0, 0, 0)));
	font_install_glyph(f, 'Q', GLY5(ROW(0, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 1, 1), ROW(0, 1, 1, 1, 1)));
	font_install_glyph(f, 'R', GLY5(ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 0, 1),
			ROW(1, 1, 1, 1, 0), ROW(1, 0, 0, 1, 0), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'S', GLY5(ROW(0, 1, 1, 1, 1), ROW(1, 0, 0, 0, 0),
			ROW(0, 1, 1, 1, 0), ROW(0, 0, 0, 0, 1), ROW(1, 1, 1, 1, 0)));
	font_install_glyph(f, 'T', GLY5(ROW(1, 1, 1, 1, 1), ROW(0, 0, 1, 0, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, 'U', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1), ROW(0, 1, 1, 1, 0)));
	font_install_glyph(f, 'V', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 0, 0, 1), ROW(0, 1, 0, 1, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, 'W', GLY5(ROW(1, 0, 0, 0, 1), ROW(1, 0, 0, 0, 1),
			ROW(1, 0, 1, 0, 1), ROW(1, 1, 0, 1, 1), ROW(1, 0, 0, 0, 1)));
	font_install_glyph(f, 'X', GLY5(ROW(1, 0, 0, 0, 1), ROW(0, 1, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 1, 0), ROW(1, 0, 0, 0, 1)));
}

void	install_uppercase_y_z(t_font *f)
{
	font_install_glyph(f, 'Y', GLY5(ROW(1, 0, 0, 0, 1), ROW(0, 1, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0), ROW(0, 0, 1, 0, 0)));
	font_install_glyph(f, 'Z', GLY5(ROW(1, 1, 1, 1, 1), ROW(0, 0, 0, 1, 0),
			ROW(0, 0, 1, 0, 0), ROW(0, 1, 0, 0, 0), ROW(1, 1, 1, 1, 1)));
}
