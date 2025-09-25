#ifndef FONT5_H
# define FONT5_H

# include <stddef.h>
# include <stdint.h>

# ifndef FONT5_HAS_T_IMG

typedef struct s_img	t_img;
# endif

# define FONT5_COLS 5
# define FONT5_ROWS 5

# define ROW_00000 0x00
# define ROW_00001 0x08
# define ROW_00010 0x10
# define ROW_00011 0x18
# define ROW_00100 0x20
# define ROW_00101 0x28
# define ROW_00110 0x30
# define ROW_00111 0x38
# define ROW_01000 0x40
# define ROW_01001 0x48
# define ROW_01010 0x50
# define ROW_01011 0x58
# define ROW_01100 0x60
# define ROW_01101 0x68
# define ROW_01110 0x70
# define ROW_01111 0x78
# define ROW_10000 0x80
# define ROW_10001 0x88
# define ROW_10010 0x90
# define ROW_10011 0x98
# define ROW_10100 0xA0
# define ROW_10101 0xA8
# define ROW_10110 0xB0
# define ROW_10111 0xB8
# define ROW_11000 0xC0
# define ROW_11001 0xC8
# define ROW_11010 0xD0
# define ROW_11011 0xD8
# define ROW_11100 0xE0
# define ROW_11101 0xE8
# define ROW_11110 0xF0
# define ROW_11111 0xF8

/* 5x5 bitmap glyph: use top-5 bits of each row (bits 7..3) */
typedef struct s_glyph5
{
	uint8_t	rows[FONT5_ROWS];
}	t_glyph5;

# ifndef FONT5_NO_GEOM

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;
typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;
# endif

/* Font container: 256 glyph slots + presence map + fallback char */
typedef struct s_font
{
	t_glyph5		glyphs[256];
	int				has_glyph[256];
	unsigned char	fallback;
}	t_font;

/* Text style (format) */
typedef struct s_textfmt
{
	int				size;
	int				spacing;
	int				color;
}	t_textfmt;

/* Draw request: single-line, left-aligned at pos */
typedef struct s_textdraw
{
	t_img			*img;
	const t_font	*font;
	const char		*str;
	t_point			pos;
	t_textfmt		fmt;
}	t_textdraw;

/* Centered draw request: string centered inside frame rect */
typedef struct s_textcenter
{
	t_img			*img;
	const t_font	*font;
	const char		*str;
	t_rect			frame;
	t_textfmt		fmt;
}	t_textcenter;

void	install_digits_0_9(t_font *f);
void	install_uppercase_a_l(t_font *f);
void	install_uppercase_m_x(t_font *f);
void	install_uppercase_y_z(t_font *f);
/* -------------------------------------------------------------------------- */
/* Lifecycle                                                                  */
/* -------------------------------------------------------------------------- */
t_font	*font_create(void);
void	font_destroy(t_font **pf);
int		font_install_glyph(t_font *f, unsigned char ch, t_glyph5 g);

/* -------------------------------------------------------------------------- */
/* Metrics                                                                    */
/* -------------------------------------------------------------------------- */
int		text_line_height(int size);
int		text_measure_width(const t_font *f,
			const char *s, int size, int spacing);

/* -------------------------------------------------------------------------- */
/* Rendering                                                                  */
/* -------------------------------------------------------------------------- */
void	text_draw(const t_textdraw *td);
void	text_draw_centered(const t_textcenter *tc);

/* -------------------------------------------------------------------------- */
/* Safe pixel & rectangle fill                                                */
/* -------------------------------------------------------------------------- */
void	pixel_put_safe(t_img *img, int x, int y, int color);
void	fill_rect_safe(t_img *img, t_rect r, int color);

/* -------------------------------------------------------------------------- */
/* Port layer																  */
/* -------------------------------------------------------------------------- */
int		font5_img_w(const t_img *img);
int		font5_img_h(const t_img *img);

#endif
