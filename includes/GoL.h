#ifndef GOL_H
# define GOL_H

# include <stdint.h>
# include "libft.h"
# include "mlx.h"

/* ---------- Enums & constantes ---------- */

typedef enum e_border
{
	BORDER_CLAMP = 0,     /* bords morts */
	BORDER_TORE  = 1      /* wrap/torus   */
}	t_border;

typedef enum e_runstate
{
	RUN_PAUSED = 0,
	RUN_PLAY   = 1
}	t_runstate;

# define INIT_NONE 0
# define INIT_MLX 2
# define INIT_WIN 4
# define INIT_IMG 16
# define INIT_

/* ---------- Types basiques utilitaires ---------- */

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

/* ---------- Monde (simulation) ---------- */
/* Dense : 1 octet par cellule (0/1), double-buffer pour step sûr. */

typedef struct s_world
{
	int         w;           /* largeur totale de la grille (cellules)   */
	int         h;           /* hauteur totale de la grille (cellules)   */
	t_border    border;      /* mode de bord : CLAMP ou TORE             */

	uint8_t    *cur;         /* buffer courant (lecture)  taille = w*h   */
	uint8_t    *nxt;         /* buffer suivant (écriture) taille = w*h   */

	unsigned    gen;         /* génération courante                       */
	unsigned    population;  /* nb de cellules vivantes après dernier step*/
}	t_world;

/* ---------- Vue (caméra / viewport) ---------- */
/* Affiche seulement une fenêtre sur le monde, avec zoom cellulaire. */

typedef struct s_view
{
	int	cell_px;    /* taille d'une cellule en pixels (>=1)           */
	int	ox;         /* offset monde -> écran (cellules, coin haut-g.) */
	int	oy;         /* idem                                           */

	/* Garde-fous UX */
	int	cell_px_min;
	int	cell_px_max;
}	t_view;

/* ---------- Image MLX (framebuffer logiciel) ---------- */

typedef struct s_img
{
	void	*img;       /* handle MLX */
	char	*addr;      /* addr mémoire de l'image */
	int		bpp;        /* bits per pixel (attendu 32) */
	int		ll;         /* line length (octets par ligne) */
	int		endian;     /* endianness MLX */
	int		w;          /* largeur image en pixels */
	int		h;          /* hauteur image en pixels */
}	t_img;

/* ---------- Contexte MLX ---------- */

typedef struct s_gfx
{
	void	*mlx;
	void	*win;
	t_img	frame;      /* image unique blitée chaque frame */
	int		win_w;      /* taille fenêtre */
	int		win_h;
}	t_gfx;

/* ---------- Entrées (état des touches/souris) ---------- */

typedef struct s_input
{
	int	key_up;      /* bool-like (0/1) */
	int	key_down;
	int	key_left;
	int	key_right;

	int	key_step;    /* step 1 tick si pause */
	int	key_speed_up;
	int	key_speed_dn;
	int	key_toggle_border;

	int	mouse_down;  /* drag pour pan */
	int	mouse_x;
	int	mouse_y;
	int	mouse_wheel; /* -1 / 0 / +1 sur l’itération */
}	t_input;

/* ---------- Horloge / cadence ---------- */
/* Timestep fixe pour la simulation, indépendamment du FPS rendu. */

typedef struct s_clock
{
	double  target_tps;   /* ticks (steps) par seconde désirés */
	double  acc;          /* accumulateur de temps */
	double  last_ms;      /* timestamp ms dernière frame */
}	t_clock;

/* ---------- Config au lancement ---------- */

typedef struct s_cfg
{
	int         world_w;         /* ex. 2048 */
	int         world_h;         /* ex. 2048 */
	t_border    border_default;  /* CLAMP ou TORE */
	double      start_tps;       /* ex. 20.0 */
	int         start_cell_px;   /* ex. 8 */
	int         start_density;   /* 0..100 pour seed aléatoire (%) */
}	t_cfg;

/* ---------- App (agrégat central) ---------- */
/* Permet de passer ≤ 4 paramètres aux fonctions en ne passant que t_app*. */

typedef struct s_app
{
	int			init_status;
	t_cfg       cfg;
	t_world     world;
	t_view      view;
	t_gfx       gfx;
	t_input     in;
	t_clock     clk;
	t_runstate  run;
}	t_app;








/* ---------- Prototypes majeurs ---------- */

/* init / teardown */
// int   app_init(t_app *a);        /* alloue world, crée MLX, image, vue */
// void  app_destroy(t_app *a);

/* monde */
int   world_alloc(t_world *w, int W, int H, t_border b);
void  world_free(t_world *w);
void  world_clear(t_world *w);
void  world_seed_random(t_world *w, int percent);

/* step */
void  world_step_dense(t_world *w);                /* lit cur, écrit nxt, swap+stats */

/* voisinage (helpers inline dans le .c) */
// static inline int count_neighbors_clamp(const t_world *w, int x, int y);
// static inline int count_neighbors_tore(const t_world *w, int x, int y);

/* rendu */
int   gfx_init(t_gfx *g, int win_w, int win_h, const char *title);
void  gfx_destroy(t_gfx *g);
void  frame_clear(t_img *img, uint32_t argb);
void  frame_fill_rect(t_img *img, t_rect r, uint32_t argb);
void  draw_world_to_frame(const t_world *w, const t_view *v, t_img *dst);

/* vue */
void  view_center_on(t_view *v, int cx, int cy, const t_gfx *g);
void  view_zoom(t_view *v, int delta, t_point pivot_scr, t_gfx *g); /* zoom autour du curseur */
void  view_pan(t_view *v, int dx_cells, int dy_cells);

/* input & loop */
void  input_begin_frame(t_input *in);            /* reset wheel, step, etc. */
void  handle_key_event(t_app *a, int keycode, int pressed);
void  handle_mouse_event(t_app *a, int x, int y, int type, int delta);
void  app_update(t_app *a);                      /* cadence fixe: run ticks, puis rendre */
void  app_render(t_app *a);                      /* blit unique via mlx_put_image_to_window */

#endif
