#ifndef GOL_DEF_H
# define GOL_DEF_H

# include <stdint.h>
# include <time.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_font	t_font;

/* ---------- Enums & constantes ---------- */

typedef enum e_border
{
	BORDER_CLAMP = 0,
	BORDER_TORE = 1
}	t_border;

typedef enum e_runstate
{
	RUN_PAUSED = 0,
	RUN_PLAY = 1
}	t_runstate;

# define INIT_NONE 0
# define INIT_MLX 1
# define INIT_WIN 2
# define INIT_IMG 4
# define INIT_WORLD 8
# define INIT_FONT 16

# define TILE_SIZE 64

# define TPS_MIN 0.2
# define TPS_MAX 300.0

# define CAMERA_BASE_PX_PER_SEC 800.0

/* ---------- Types basiques utilitaires ---------- */

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;

/* ---------- Monde (simulation) ---------- */
/* Dense : 1 octet par cellule (0/1), double-buffer pour step sûr. */

typedef struct s_world
{
	int				w;
	int				h;
	t_border		border;
	uint8_t			*cur;
	uint8_t			*next;
	unsigned int	gen;
	unsigned int	population;
}					t_world;

/* ---------- Vue (caméra / viewport) ---------- */
/* Affiche seulement une fenêtre sur le monde, avec zoom cellulaire. */

typedef struct s_view
{
	int				cell_px;
	int				offset_x;
	int				offset_y;
	int				cell_px_min;
	int				cell_px_max;
}					t_view;

typedef struct s_zoom_ctx
{
	int				new_cell_px;
	int				old_cell_px;
	t_point			pivot_screen;
}					t_zoom_ctx;

/* ---------- Image MLX (framebuffer logiciel) ---------- */

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
	int				w;
	int				h;
}					t_img;

/* ---------- Contexte MLX ---------- */

typedef struct s_gfx
{
	void			*mlx;
	void			*win;
	t_img			frame;
	int				win_w;
	int				win_h;
}					t_gfx;

/* ---------- Entrées (état des touches/souris) ---------- */

typedef struct s_input
{
	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;

	int				req_toggle_run;
	int				req_step_once;
	int				req_speed_up;
	int				req_speed_down;
	int				req_toggle_border;
	int				req_clear_world;
	int				req_reseed_world;

	int				req_zoom_in;
	int				req_zoom_out;

	int				mouse_dragging;
	int				drag_px_acc_x;
	int				drag_px_acc_y;
	int				mouse_last_x;
	int				mouse_last_y;
}					t_input;

/* ---------- Horloge / cadence ---------- */
/* Timestep fixe pour la simulation, indépendamment du FPS rendu. */

typedef struct s_clock
{
	double			target_tps;
	double			acc;
	double			last_ms;
}					t_clock;

/* ---------- Config au lancement ---------- */

typedef struct s_cfg
{
	int				world_w;
	int				world_h;
	t_border		border_default;
	double			start_tps;
	int				start_cell_px;
	int				start_density;
}					t_cfg;

/* ---------- App (agrégat central) ---------- */
/* Permet de passer ≤ 4 paramètres aux fonctions en ne passant que t_app*. */

typedef struct s_app
{
	int				init_status;
	t_cfg			cfg;
	t_world			world;
	t_view			view;
	t_gfx			gfx;
	t_input			in;
	t_clock			clk;
	t_runstate		run;
	t_font			*ui_font;
}					t_app;

#endif
