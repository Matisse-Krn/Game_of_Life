#include "GoL.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define GUARD_BYTES 32

static void	assert_guards(const unsigned char *raw, size_t bytes)
{
	size_t	i;

	i = 0;
	while (i < GUARD_BYTES)
	{
		assert(raw[i] == 0xA5);
		assert(raw[GUARD_BYTES + bytes + i] == 0xA5);
		i++;
	}
}

static void	assert_has_pixels(const t_img *frame)
{
	size_t	i;
	size_t	bytes;

	bytes = (size_t)frame->ll * (size_t)frame->h;
	i = 0;
	while (i < bytes && frame->addr[i] == 0)
		i++;
	assert(i < bytes);
}

static void	test_draw_at_size(t_app *app, int width, int height)
{
	unsigned char	*raw;
	size_t			bytes;
	char			line[128];
	int				pixel;

	bytes = (size_t)width * (size_t)height * 4;
	raw = malloc(bytes + 2 * GUARD_BYTES);
	assert(raw);
	memset(raw, 0xA5, bytes + 2 * GUARD_BYTES);
	app->gfx.win_w = width;
	app->gfx.win_h = height;
	app->gfx.frame = (t_img){0};
	app->gfx.frame.addr = (char *)(raw + GUARD_BYTES);
	app->gfx.frame.w = width;
	app->gfx.frame.h = height;
	app->gfx.frame.bpp = 32;
	app->gfx.frame.ll = width * 4;
	clear_frame(&app->gfx.frame);
	app->hud_visible = 1;
	hud_draw(app);
	assert_has_pixels(&app->gfx.frame);
	assert_guards(raw, bytes);
	if (width >= 500 && height >= 300)
	{
		memcpy(&pixel, app->gfx.frame.addr
			+ HUD_MARGIN_PX * app->gfx.frame.ll + HUD_MARGIN_PX * 4, 4);
		assert((unsigned int)pixel == HUD_COLOR_BORDER);
	}
	status_line_text(app, 0, line, (int)sizeof(line));
	assert(strstr(line, "GEN 42") != NULL);
	app->in.req_toggle_hud = 1;
	handle_toggle_hud(app);
	assert(!app->hud_visible && !app->in.req_toggle_hud);
	clear_frame(&app->gfx.frame);
	hud_draw(app);
	assert(app->gfx.frame.addr[0] == 0);
	assert_guards(raw, bytes);
	free(raw);
	app->gfx.frame.addr = NULL;
}

int	main(void)
{
	t_app	app;
	uint8_t	cells[20 * 20];
	char	tiny[5];

	app = (t_app){0};
	ft_bzero(cells, sizeof(cells));
	app.ui_font = font_create();
	assert(app.ui_font && app.ui_font->has_glyph['?']);
	app.world.w = 20;
	app.world.h = 20;
	app.world.cur = cells;
	app.world.gen = 42;
	app.world.population = 1;
	app.view.cell_px = 8;
	app.clk.target_tps = 20.0;
	app.run = RUN_PLAY;
	app.in.mouse_last_x = 25;
	app.in.mouse_last_y = 35;
	buf_reset(tiny);
	buf_cat_str(tiny, (int)sizeof(tiny), "abcdef");
	assert(strcmp(tiny, "abcd") == 0);
	test_draw_at_size(&app, 1600, 900);
	test_draw_at_size(&app, 160, 100);
	font_destroy(&app.ui_font);
	assert(app.ui_font == NULL);
	puts("HUD renderer tests: OK");
	return (0);
}
