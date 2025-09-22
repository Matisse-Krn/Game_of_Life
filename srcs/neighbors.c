#include "GoL.h"

int	count_neighbors_clamp(const t_world *world, int cx, int cy)
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
			if (dx || dy)
			{
				nx = cx + dx;
				ny = cy + dy;
				if (nx >= 0 && ny >= 0 && nx < world->w && ny < world->h)
					sum += (world->cur[ny * world->w + nx] != 0);
			}
			dx++;
		}
		dy++;
	}
	return (sum);
}

int	count_neighbors_tore(const t_world *world, int cx, int cy)
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
			if (dx || dy)
			{
				nx = cx + dx;
				ny = cy + dy;
				if (nx < 0) nx = world->w - 1; else if (nx >= world->w) nx = 0;
				if (ny < 0) ny = world->h - 1; else if (ny >= world->h) ny = 0;
				sum += (world->cur[ny * world->w + nx] != 0);
			}
			dx++;
		}
		dy++;
	}
	return (sum);
}

int	is_cell_alive_next(const t_world *world, int x, int y)
{
	int	index;
	int	neighbors;
	int	alive_now;
	int	alive_next;

	index = y * world->w + x;
	if (world->border == BORDER_TORE)
		neighbors = count_neighbors_tore(world, x, y);
	else
		neighbors = count_neighbors_clamp(world, x, y);
	alive_now = (world->cur[index] != 0);
	alive_next = 0;
	if (neighbors == 3)
		alive_next = 1;
	else if (alive_now && neighbors == 2)
		alive_next = 1;
	return (alive_next);
}
