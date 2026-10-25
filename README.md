# Game of Life — HUD branch (0.5.0)

An interactive implementation of Conway's Game of Life in C, using the Linux
MiniLibX (X11). The simulation has a 2048 × 2048 cell grid, toroidal or bounded
edges, a movable camera, zoom and adjustable simulation speed.

## Requirements

Linux with an X11 server (or an XWayland-compatible desktop), a C compiler,
GNU Make, Git and MiniLibX's X11 development dependencies.

Debian / Ubuntu:

```sh
sudo apt update
sudo apt install build-essential git libx11-dev libxext-dev libbsd-dev
```

## Build and run

```sh
make -j"$(nproc)"
./game_of_life
```

The Makefile downloads MiniLibX and [libft](https://github.com/Matisse-Krn/libft)
automatically. Both are pinned to revisions used with this snapshot, so
rebuilding later does not silently change their source code.

| Command | Effect |
| --- | --- |
| `make` | Build and link the program, fetching dependencies when absent |
| `make -j4` | Build with four parallel jobs |
| `make test` | Run headless simulation regression tests |
| `make clean` | Remove object files and build products of local dependencies |
| `make fclean` | Also remove the executable and libft static library |
| `make re` | Clean and rebuild all components |
| `make aclean` | Remove downloaded `mlx_linux/` and `libft/` directories too |
| `make rr` | Download pinned dependencies again and fully rebuild |

`aclean` and `rr` delete the locally downloaded dependency directories,
including any changes made inside them. They do not delete the game's source
files.

## Controls

| Input | Action |
| --- | --- |
| H | Show / hide the HUD |
| Space | Pause / resume |
| N (while paused) | Advance one generation |
| Arrow keys | Pan the camera |
| + / - | Zoom in / out |
| Page Up / Page Down | Increase / decrease simulation speed |
| B | Toggle toroidal / bounded edges |
| C | Clear all cells |
| R | Generate a new random state |
| Mouse drag | Move the camera |
| Mouse wheel | Zoom |
| Esc | Exit |

## GCC 15 / C23 compatibility

Starting with GCC 15, the default language mode is GNU C23. MiniLibX's
`mlx_hook` and `mlx_loop_hook` declare callbacks as `int (*)()`, which
means **a function taking no arguments** in C23. The application's handlers
actually receive event data and an application pointer. With
`-Wincompatible-pointer-types` and `-Werror`, compilation therefore fails.

This project explicitly uses `-std=gnu17` when compiling its sources and
libft. That preserves the historical meaning of MiniLibX's callback
declarations without changing the event handlers or suppressing warnings.
MiniLibX itself is built with its upstream Makefile.

To diagnose a failed build, leave the compiler output visible and check that
the X11 development packages listed above are installed. Compilation does
not require a running graphical session, but launching the executable does.

The experimental HUD draws a simulation status panel, a key help panel and
current mouse-cell information using a built-in 5×5 bitmap font. It renders
into the same framebuffer as the cellular world.

MiniLibX upstream: https://github.com/42paris/minilibx-linux

The regression tests cover a stable block, a two-generation blinker,
toroidal versus bounded edges, random seeding and reset operations, plus HUD
text/panel rendering into a guarded memory buffer (including a small window)
and HUD visibility toggling. They do not require a graphical session.
