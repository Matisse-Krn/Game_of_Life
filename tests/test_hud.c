#include "GoL.h"
#include <assert.h>
#include <limits.h>
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

static void	test_rectangle_clipping(void)
{
	uint32_t	pixels[16 * 16];
	t_img		frame;
	int			x;
	int			y;

	frame = (t_img){0};
	frame.addr = (char *)pixels;
	frame.w = 16;
	frame.h = 16;
	frame.bpp = 32;
	frame.ll = 16 * 4;
	memset(pixels, 0, sizeof(pixels));
	fill_rect_safe(&frame, (t_rect){-5, 2, 10, 3}, 0x123456);
	y = -1;
	while (++y < 16)
	{
		x = -1;
		while (++x < 16)
			assert(pixels[y * 16 + x]
				== (uint32_t)((y >= 2 && y < 5 && x < 5) * 0x123456));
	}
	memset(pixels, 0, sizeof(pixels));
	fill_rect_safe(&frame, (t_rect){3, -4, 3, 6}, 0xABCDEF);
	y = -1;
	while (++y < 16)
	{
		x = -1;
		while (++x < 16)
			assert(pixels[y * 16 + x]
				== (uint32_t)((y < 2 && x >= 3 && x < 6) * 0xABCDEF));
	}
	fill_rect_safe(&frame, (t_rect){INT_MAX, 0, INT_MAX, 3}, 0x123456);
	assert(pixels[0] == 0);
}

static void	test_draw_at_size(t_app *app, int width, int height)
{
	unsigned char	*raw;
	size_t			bytes;
	char			line[128];
	int				pixel;
	t_rect			status;

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
	status = hud_status_panel_rect(app);
	if (status.w > 0)
	{
		assert(status.x >= 0 && status.y >= 0);
		assert(status.x + status.w <= width);
		assert(status.y + status.h <= height);
	}
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
	test_rectangle_clipping();
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
	{
		char min_value[24];

		buf_reset(min_value);
		buf_cat_i32(min_value, (int)sizeof(min_value), INT_MIN);
		assert(strcmp(min_value, "-2147483648") == 0);
	}
	test_draw_at_size(&app, 1600, 900);
	test_draw_at_size(&app, 800, 600);
	test_draw_at_size(&app, 320, 240);
	test_draw_at_size(&app, 160, 100);
	font_destroy(&app.ui_font);
	assert(app.ui_font == NULL);
	puts("HUD renderer tests: OK");
	return (0);
}
