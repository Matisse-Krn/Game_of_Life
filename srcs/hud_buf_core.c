#include "GoL.h"

void	buf_reset(char *dst)
{
	if (dst)
		dst[0] = '\0';
}

void	buf_cat_str(char *dst, int cap, const char *src)
{
	if (!dst || !src || cap <= 0)
		return ;
	(void)ft_strlcat(dst, src, (size_t)cap);
}

void	buf_cat_char(char *dst, int cap, char c)
{
	size_t	n;

	if (!dst || cap <= 0)
		return ;
	n = ft_strlen(dst);
	if ((int)n + 1 < cap)
	{
		dst[n] = c;
		dst[n + 1] = '\0';
	}
}

void	buf_cat_u32(char *dst, int cap, unsigned int v)
{
	char	tmp[16];
	int		i;

	if (v == 0)
	{
		buf_cat_char(dst, cap, '0');
		return ;
	}
	i = 0;
	while (v > 0 && i < 15)
	{
		tmp[i] = (char)('0' + (v % 10));
		v = v / 10;
		i++;
	}
	i = i - 1;
	while (i >= 0)
	{
		buf_cat_char(dst, cap, tmp[i]);
		i = i - 1;
	}
}

void	buf_cat_i32(char *dst, int cap, int v)
{
	unsigned int	u;

	if (v < 0)
	{
		buf_cat_char(dst, cap, '-');
		u = (unsigned int)(-v);
	}
	else
		u = (unsigned int)v;
	buf_cat_u32(dst, cap, u);
}
