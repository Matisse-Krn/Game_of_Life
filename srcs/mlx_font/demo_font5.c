#include "font5.h"

/* -------------------------------------------------------------------------- */
/* Helpers (petits, Norme OK)                                                 */
/* -------------------------------------------------------------------------- */

static t_textfmt	f5_fmt(int size, int color)
{
	t_textfmt	fmt;

	fmt.size = size;
	fmt.spacing = TEXT_DEFAULT_SPACING(size);
	fmt.color = color;
	return (fmt);
}

static void	demo_line(t_textdraw *td, int y, const char *s)
{
	td->pos.x = 16;
	td->pos.y = y;
	td->str = s;
	text_draw(td);
}

static int	demo_block_sets(t_textdraw *td, int y)
{
	int	line_h;
	int	gap;

	td->fmt = f5_fmt(4, 0xFFFFFFFF);
	line_h = text_line_height(td->fmt.size);
	gap = 6;
	demo_line(td, y, "digits: 0123456789");
	y += line_h + gap;
	demo_line(td, y, "upper:  abcdefghijklmnopqrstuvwxyz");
	y += line_h + gap;
	demo_line(td, y, "punct:  .,:;!?-+=%/|\\()[]<>");
	y += line_h + gap + 8;
	return (y);
}

static int	demo_block_sizes(t_textdraw *td, int y0)
{
	int	sz;
	int	y;
	int	gap;

	y = y0;
	sz = 1;
	while (sz <= 18)
	{
		td->fmt = f5_fmt(sz, 0xFFE6E6E6);
		gap = 4 + sz;
		demo_line(td, y, "abcdefghijklmnopqrstuvwxyz"
			"0123456789 .,:;!?-+=%/|\\()[]<>");
		y += text_line_height(td->fmt.size) + gap;
		sz++;
	}
	return (y);
}

/* -------------------------------------------------------------------------- */
/* API : à appeler depuis ta boucle pour voir la page de test                 */
/* -------------------------------------------------------------------------- */

void	demo_font5_on_frame(t_img *dst)
{
	t_font		*f;
	t_textdraw	td;
	int			y;

	if (!dst)
		return ;
	f = font_create();
	if (!f)
		return ;
	td.img = dst;
	td.font = f;
	td.pos.x = 16;
	td.pos.y = 16;
	td.fmt = f5_fmt(4, 0xFFFFFFFF);
	demo_line(&td, 16, "FONT5 DEMO (5x5 scalable)");
	y = demo_block_sets(&td, 16 + text_line_height(4) + 10);
	(void)demo_block_sizes(&td, y);
	font_destroy(&f);
}
