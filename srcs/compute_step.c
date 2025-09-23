#include "GoL.h"

static inline int	wrap_index(int v, int max)
{
	if (v < 0)
		return (max - 1);
	if (v >= max)
		return (0);
	return (v);
}

static inline int	count_neighbors_tore_inline(const t_world *w,
	int cx, int cy)
{
	int	dy;
	int	dx;
	int	nx;
	int	ny;
	int	sum;

	sum = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dx != 0 || dy != 0)
			{
				nx = wrap_index(cx + dx, w->w);
				ny = wrap_index(cy + dy, w->h);
				sum += (w->cur[ny * w->w + nx] != 0);
			}
			dx++;
		}
		dy++;
	}
	return (sum);
}

static inline int	count_neighbors_clamp_inline(const t_world *w,
	int cx, int cy)
{
	int	dy;
	int	dx;
	int	nx;
	int	ny;
	int	sum;

	sum = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dx != 0 || dy != 0)
			{
				nx = cx + dx;
				ny = cy + dy;
				if (nx >= 0 && ny >= 0 && nx < w->w && ny < w->h)
					sum += (w->cur[ny * w->w + nx] != 0);
			}
			dx++;
		}
		dy++;
	}
	return (sum);
}

static inline int	count_neighbors_inline(const t_world *w, int x, int y)
{
	if (w->border == BORDER_TORE)
		return (count_neighbors_tore_inline(w, x, y));
	return (count_neighbors_clamp_inline(w, x, y));
}

static t_rect	make_tile_rect(int x0, int y0, const t_world *w)
{
	t_rect	r;

	r.x = x0;
	r.y = y0;
	r.w = TILE_SIZE;
	if (r.x + r.w > w->w)
		r.w = w->w - r.x;
	r.h = TILE_SIZE;
	if (r.y + r.h > w->h)
		r.h = w->h - r.y;
	return (r);
}

static int	step_tile_sum(t_world *w, t_rect r)
{
	int	y;
	int	x;
	int	idx;
	int	living;
	int	n;

	living = 0;
	y = -1;
	while (++y < r.h)
	{
		x = -1;
		idx = (r.y + y) * w->w + r.x;
		while (++x < r.w)
		{
			n = count_neighbors_inline(w, r.x + x, r.y + y);
			w->next[idx] = (n == 3) || (w->cur[idx] && n == 2);
			living += w->next[idx];
			idx++;
		}
	}
	return (living);
}

static void	world_swap_buffers(t_world *w)
{
	uint8_t	*tmp;

	tmp = w->cur;
	w->cur = w->next;
	w->next = tmp;
}

void	world_step_dense(t_world *w)
{
	int		y0;
	int		x0;
	int		living_total;
	t_rect	t;

	if (!w || !w->cur || !w->next)
		return ;
	living_total = 0;
	y0 = 0;
	while (y0 < w->h)
	{
		x0 = 0;
		while (x0 < w->w)
		{
			t = make_tile_rect(x0, y0, w);
			living_total += step_tile_sum(w, t);
			x0 += TILE_SIZE;
		}
		y0 += TILE_SIZE;
	}
	world_swap_buffers(w);
	w->population = (unsigned)living_total;
	w->gen++;
}
