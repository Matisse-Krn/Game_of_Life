#include "font5.h"

int	text_line_height(int size)
{
	if (size <= 0)
		return (0);
	return (FONT5_ROWS * size);
}

static int	s_len(const char *s)
{
	int	n;

	if (!s)
		return (0);
	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	text_measure_width(const t_font *f, const char *s, int size, int spacing)
{
	int	len;
	int	char_w;

	(void)f;
	if (!s || size <= 0)
		return (0);
	if (spacing < 0)
		spacing = 0;
	len = s_len(s);
	if (len == 0)
		return (0);
	char_w = FONT5_COLS * size;
	return (len * char_w + (len - 1) * spacing);
}
