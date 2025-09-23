#ifndef GOL_DEF_H
# define GOL_DEF_H

# include <stdint.h>
# include <time.h>
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
# define INIT_MLX 1
# define INIT_WIN 2
# define INIT_IMG 4
# define INIT_WORLD 8

# define TILE_SIZE 64

# define ESC 65307

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
	uint8_t    *next;         /* buffer suivant (écriture) taille = w*h   */

	unsigned    gen;         /* génération courante                       */
	unsigned    population;  /* nb de cellules vivantes après dernier step*/
}	t_world;

/* ---------- Vue (caméra / viewport) ---------- */
/* Affiche seulement une fenêtre sur le monde, avec zoom cellulaire. */

typedef struct s_view
{
	int	cell_px;    /* taille d'une cellule en pixels (>=1)           */
	int	offset_x;         /* offset monde -> écran (cellules, coin haut-g.) */
	int	offset_y;         /* idem                                           */
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








#endif
