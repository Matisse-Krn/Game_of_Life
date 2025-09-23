#ifndef GOL_H
# define GOL_H

# include "GoL_def.h"
# include "GoL_keys.h"

/* init / teardown */
int	app_init(t_app *app);        /* alloue world, crée MLX, image, vue */
int	world_alloc(t_world *world, int grid_w, int grid_h, t_border border_mode);
void	world_seed_random(t_world *world, int percent);
void	world_clear(t_world *world);
int	app_destroy(t_app *app, int exit_code);
int	on_close(t_app *app);
// MLX init
int	init_mlx_basics(t_app *app);
int	init_mlx_image(t_app *app);
void	init_view_defaults(t_app *app);

// void  app_destroy(t_app *a);

/* monde */
// int   world_alloc(t_world *w, int W, int H, t_border b);
// void  world_free(t_world *w);
// void  world_clear(t_world *w);
// void  world_seed_random(t_world *w, int percent);

/* time */
double	now_ms(void);
void	init_clock_defaults(t_app *app);
void	loop_do_steps(t_app *app, double dt_ms);

/* step */
// void  world_step_dense(t_world *w);                /* lit cur, écrit nxt, swap+stats */
void	world_step_dense(t_world *world);

/* voisinage (helpers inline dans le .c) */
// static inline int count_neighbors_clamp(const t_world *w, int x, int y);
// static inline int count_neighbors_tore(const t_world *w, int x, int y);

/* rendu */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
// int   gfx_init(t_gfx *g, int win_w, int win_h, const char *title);
// void  gfx_destroy(t_gfx *g);
void	clear_frame(t_img *img);
// void  frame_clear(t_img *img, uint32_t argb);
void	frame_fill_rect(t_img *img, t_rect rect, unsigned int argb);
// void  frame_fill_rect(t_img *img, t_rect r, uint32_t argb);
// void  draw_world_to_frame(const t_world *w, const t_view *v, t_img *dst);
void	draw_world_to_frame(const t_world *world, const t_view *view, t_img *dst);

/* vue */
// void  view_center_on(t_view *v, int cx, int cy, const t_gfx *g);
// void  view_zoom(t_view *v, int delta, t_point pivot_scr, t_gfx *g); /* zoom autour du curseur */
// void  view_pan(t_view *v, int dx_cells, int dy_cells);

/* input & loop */
// void  input_begin_frame(t_input *in);            /* reset wheel, step, etc. */
int	on_key_press(int keycode, t_app *app);
int	on_key_release(int keycode, t_app *app);
void	input_begin_frame(t_input *in);
void	apply_input_core(t_app *a);
// void  handle_key_event(t_app *a, int keycode, int pressed);
// void  handle_mouse_event(t_app *a, int x, int y, int type, int delta);
// void  app_update(t_app *a);                      /* cadence fixe: run ticks, puis rendre */
// void  app_render(t_app *a);                      /* blit unique via mlx_put_image_to_window */

#endif
