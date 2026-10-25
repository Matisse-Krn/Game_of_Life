#include "GoL.h"
#include <assert.h>
#include <stdio.h>

static void release_world(t_world *w)
{
	free(w->cur);
	free(w->next);
}

static void set_alive(t_world *w, int x, int y)
{
	w->cur[y * w->w + x] = 1;
	w->population++;
}

static void assert_pattern(t_world *w, const t_point *cells, int count)
{
	int x;
	int y;
	int i;
	int alive;

	assert(w->population == (unsigned)count);
	y = -1;
	while (++y < w->h)
	{
		x = -1;
		while (++x < w->w)
		{
			alive = 0;
			i = -1;
			while (++i < count)
				if (cells[i].x == x && cells[i].y == y)
					alive = 1;
			assert(w->cur[y * w->w + x] == alive);
		}
	}
}

static void test_still_life(void)
{
	t_world w = {0};
	const t_point block[] = {{1, 1}, {2, 1}, {1, 2}, {2, 2}};

	assert(world_alloc(&w, 5, 5, BORDER_CLAMP));
	set_alive(&w, 1, 1);
	set_alive(&w, 2, 1);
	set_alive(&w, 1, 2);
	set_alive(&w, 2, 2);
	world_step_dense(&w);
	assert(w.gen == 1);
	assert_pattern(&w, block, 4);
	release_world(&w);
}

static void test_oscillator(void)
{
	t_world w = {0};
	const t_point vertical[] = {{2, 1}, {2, 2}, {2, 3}};
	const t_point horizontal[] = {{1, 2}, {2, 2}, {3, 2}};

	assert(world_alloc(&w, 5, 5, BORDER_CLAMP));
	set_alive(&w, 1, 2);
	set_alive(&w, 2, 2);
	set_alive(&w, 3, 2);
	world_step_dense(&w);
	assert(w.gen == 1);
	assert_pattern(&w, vertical, 3);
	world_step_dense(&w);
	assert(w.gen == 2);
	assert_pattern(&w, horizontal, 3);
	release_world(&w);
}

static void test_boundary_modes(void)
{
	t_world w = {0};
	const t_point wrapped[] = {{0, 1}, {0, 2}, {0, 3}};

	assert(world_alloc(&w, 5, 5, BORDER_TORE));
	set_alive(&w, 4, 2);
	set_alive(&w, 0, 2);
	set_alive(&w, 1, 2);
	world_step_dense(&w);
	assert_pattern(&w, wrapped, 3);
	release_world(&w);
	w = (t_world){0};
	assert(world_alloc(&w, 5, 5, BORDER_CLAMP));
	set_alive(&w, 4, 2);
	set_alive(&w, 0, 2);
	set_alive(&w, 1, 2);
	world_step_dense(&w);
	assert_pattern(&w, NULL, 0);
	release_world(&w);
}

static void test_reset_and_seed(void)
{
	t_world w = {0};
	int i;

	assert(!world_alloc(&w, 0, 5, BORDER_CLAMP));
	assert(world_alloc(&w, 3, 2, BORDER_CLAMP));
	world_seed_random(&w, 100);
	assert(w.population == 6 && w.gen == 0);
	i = -1;
	while (++i < 6)
		assert(w.cur[i] == 1);
	world_seed_random(&w, 0);
	assert(w.population == 0);
	i = -1;
	while (++i < 6)
		assert(w.cur[i] == 0);
	world_step_dense(&w);
	assert(w.gen == 1 && w.population == 0);
	world_clear(&w);
	assert(w.gen == 0 && w.population == 0);
	release_world(&w);
}

static void test_fixed_timestep(void)
{
	t_app app = {0};
	unsigned int gen;

	assert(world_alloc(&app.world, 5, 5, BORDER_CLAMP));
	app.run = RUN_PLAY;
	app.clk.target_tps = 100.0;
	loop_do_steps(&app, 35.0);
	assert(app.world.gen == 3);
	assert(app.clk.acc > 4.9 && app.clk.acc < 5.1);
	loop_do_steps(&app, 10.0);
	assert(app.world.gen == 4);
	app.run = RUN_PAUSED;
	loop_do_steps(&app, 1000.0);
	assert(app.world.gen == 4 && app.clk.acc == 0.0);
	app.run = RUN_PLAY;
	loop_do_steps(&app, 10.0);
	assert(app.world.gen == 5);
	gen = app.world.gen;
	loop_do_steps(&app, -10.0);
	assert(app.world.gen == gen);
	app.clk.acc = 0.0;
	app.clk.target_tps = 300.0;
	loop_do_steps(&app, 10000.0);
	assert(app.world.gen == gen + 8);
	assert(app.clk.acc >= 0.0 && app.clk.acc < 1000.0 / 300.0);
	app.clk.target_tps = 0.0;
	gen = app.world.gen;
	loop_do_steps(&app, 100.0);
	assert(app.world.gen == gen);
	release_world(&app.world);
}

int main(void)
{
	test_still_life();
	test_oscillator();
	test_boundary_modes();
	test_reset_and_seed();
	test_fixed_timestep();
	puts("World simulation tests: OK");
	return (0);
}
