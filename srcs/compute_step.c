#include "GoL.h"

static void	step_row(t_world *world, int y, int *living_out)
{
	int	x;
	int	index;
	int	alive_next;
	int	living_line;

	x = 0;
	index = y * world->w;
	living_line = 0;
	while (x < world->w)
	{
		alive_next = is_cell_alive_next(world, x, y);
		world->next[index] = (uint8_t)alive_next;
		if (alive_next)
			living_line++;
		x++;
		index++;
	}
	*living_out += living_line;
}

static void	world_swap_buffers(t_world *world)
{
	uint8_t	*tmp;

	tmp = world->cur;
	world->cur = world->next;
	world->next = tmp;
}

void	world_step_dense(t_world *world)
{
	int	y;
	int	living_total;

	if (!world || !world->cur || !world->next)
		return ;
	living_total = 0;
	y = 0;
	while (y < world->h)
	{
		step_row(world, y, &living_total);
		y++;
	}
	world_swap_buffers(world);
	world->population = (unsigned)living_total;
	world->gen++;
}
