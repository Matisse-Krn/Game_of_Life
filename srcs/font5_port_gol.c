#include "GoL_def.h"
#define FONT5_NO_GEOM
#include "font5.h"

int	font5_img_w(const t_img *img)
{
	if (!img)
		return (0);
	return (img->w);
}

int	font5_img_h(const t_img *img)
{
	if (!img)
		return (0);
	return (img->h);
}
