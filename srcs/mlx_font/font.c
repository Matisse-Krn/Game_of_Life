#include <stdlib.h>
#include "font5.h"

/* fournie par glyph_table.c */
void	font5_install_defaults(t_font *f);

static void	font_zero(t_font *f)
{
	int	i;

	if (!f)
		return ;
	i = 0;
	while (i < 256)
	{
		f->has_glyph[i] = 0;
		f->glyphs[i].rows[0] = 0;
		f->glyphs[i].rows[1] = 0;
		f->glyphs[i].rows[2] = 0;
		f->glyphs[i].rows[3] = 0;
		f->glyphs[i].rows[4] = 0;
		i++;
	}
	f->fallback = '?';
}

t_font	*font_create(void)
{
	t_font	*f;

	f = malloc(sizeof(t_font));
	if (!f)
		return (NULL);
	font_zero(f);
	font5_install_defaults(f);
	if (!f->has_glyph[(unsigned char)f->fallback])
		return (free(f), f = NULL, NULL);
	return (f);
}

void	font_destroy(t_font **pf)
{
	if (!pf || !*pf)
		return ;
	free(*pf);
	*pf = NULL;
}

int	font_install_glyph(t_font *f, unsigned char ch, t_glyph5 g)
{
	if (!f)
		return (0);
	f->glyphs[ch] = g;
	f->has_glyph[ch] = 1;
	return (1);
}
