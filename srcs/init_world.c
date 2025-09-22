#include "GoL.h"

void	world_clear(t_world *world)
{
	size_t	total_cells;

	if (!world || !world->cur || !world->next)
		return ;
	total_cells = (size_t)world->w * (size_t)world->h;
	ft_bzero(world->cur, total_cells);
	ft_bzero(world->next, total_cells);
	world->gen = 0;
	world->population = 0;
}

int	world_alloc(t_world *world, int grid_w, int grid_h, t_border border_mode)
{
	size_t	total_cells;

	if (!world || grid_w <= 0 || grid_h <= 0
		|| (size_t)grid_w > SIZE_MAX / (size_t)grid_h)
		return (FALSE);
	world->w = grid_w;
	world->h = grid_h;
	world->border = border_mode;
	world->gen = 0;
	world->population = 0;
	total_cells = (size_t)grid_w * (size_t)grid_h;
	world->cur = ft_calloc(1, total_cells);
	if (!world->cur)
		return (FALSE);
	world->next = ft_calloc(1, total_cells);
	if (!world->next)
		return (free(world->cur), world->cur = NULL, FALSE);
	return (TRUE);
}

void	world_seed_random(t_world *world, int percent)
{
	size_t	i;
	size_t	total_cells;
	int		random_value;
	int		is_alive;

	if (!world || !world->cur || !world->next)
		return ;
	if (percent < 0)
		percent = 0;
	else if (percent > 100)
		percent = 100;
	total_cells = (size_t)world->w * (size_t)world->h;
	world->population = 0;
	i = -1;
	while (++i < total_cells)
	{
		random_value = rand() % 100;
		is_alive = (random_value < percent);
		world->cur[i] = (uint8_t)is_alive;
		world->population += is_alive;
	}
	ft_bzero(world->next, total_cells);
	world->gen = 0;
}
