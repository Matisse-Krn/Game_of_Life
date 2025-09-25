#ifndef GOL_H
# define GOL_H

# include "GoL_def.h"
# include "GoL_keys.h"

# define FONT5_HAS_T_IMG 1
# define FONT5_NO_GEOM   1
# include "font5.h"
/* init / teardown */
int		app_init(t_app *app);
int		world_alloc(t_world *world, int grid_w, int grid_h,
			t_border border_mode);
void	world_seed_random(t_world *world, int percent);
void	world_clear(t_world *world);
int		app_destroy(t_app *app, int exit_code);
int		on_close(t_app *app);
// MLX init
int		init_mlx_basics(t_app *app);
int		init_mlx_image(t_app *app);
void	init_view_defaults(t_app *app);

/* time */
double	now_ms(void);
void	init_clock_defaults(t_app *app);
void	loop_do_steps(t_app *app, double dt_ms);

/* step */
void	world_step_dense(t_world *world);

/* rendu */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	clear_frame(t_img *img);
void	frame_fill_rect(t_img *img, t_rect rect, unsigned int argb);
void	draw_world_to_frame(const t_world *world, const t_view *view,
			t_img *dst);

/* HUD */
void	hud_draw(t_app *app);
void	buf_reset(char *dst);
void	buf_cat_str(char *dst, int cap, const char *src);
void	buf_cat_sep(char *dst, int cap);
void	buf_cat_char(char *dst, int cap, char c);
void	buf_cat_i32(char *dst, int cap, int v);
void	buf_cat_f1(char *dst, int cap, double x);
void	panel_draw_box(t_img *dst, t_rect box, int bg, int border);
void	draw_status_panel(t_app *app);
void	draw_help_panel(t_app *app);
void	status_line_text(t_app *app, int line_idx, char *out, int cap);
int		hud_line_step(void);
void	buf_cat_u32(char *dst, int cap, unsigned int v);

/* vue */
void	clamp_view_offsets(t_view *v, const t_world *w, const t_gfx *g);
void	view_pan_cells(t_view *view, const t_world *world,
			t_point delta_cells, const t_gfx *gfx);
void	view_zoom_at_app(t_app *app, int delta, t_point pivot_scr);
void	apply_input_camera(t_app *a, double dt_ms);
int		on_mouse_press(int button, int x, int y, t_app *app);
int		on_mouse_release(int button, int x, int y, t_app *app);
int		on_mouse_move(int x, int y, t_app *app);

/* input & loop */
int		on_key_press(int keycode, t_app *app);
int		on_key_release(int keycode, t_app *app);
void	handle_speed_adjust_requests(t_app *app);
void	handle_toggle_hud(t_app *app);
void	apply_input_core(t_app *a);

#endif
