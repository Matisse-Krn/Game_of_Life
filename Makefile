CC = cc
# MiniLibX uses int (*)() for callbacks; C23 interprets this as int (*)(void).
# GNU C17 preserves the callback signatures used by mlx_hook/ mlx_loop_hook.
CSTD = -std=gnu17
CFLAGS = -Wall -Wextra -Werror -O3 -g3 -march=native -flto
CPPFLAGS = -Imlx_linux -Ilibft/includes -Iincludes
LDFLAGS = -Lmlx_linux -Llibft
LDLIBS = -lmlx_Linux -lft -lXext -lX11 -lm

NAME = game_of_life
SRCS = srcs/compute_step.c srcs/init.c srcs/input_speed_control.c srcs/input_camera.c srcs/hud_mouse.c srcs/camera_view_utils.c srcs/time.c srcs/world_draw.c srcs/init_world.c srcs/hud_status_panel.c srcs/font5_port_gol.c srcs/input_mouse.c srcs/hud_buf_core.c srcs/image_utils.c srcs/init_mlx.c srcs/input_core2.c srcs/input_core.c srcs/input_key_actions.c srcs/camera_view.c srcs/clip_fill.c srcs/destroy.c srcs/input_keyboard.c srcs/mlx_font/glyph_table.c srcs/mlx_font/font.c srcs/mlx_font/pixel_safe.c srcs/mlx_font/demo_font5.c srcs/mlx_font/text_layout.c srcs/mlx_font/glyph_table2.c srcs/mlx_font/text_draw.c srcs/hud_status_text.c srcs/hud_help.c srcs/main.c srcs/init_view.c srcs/hud_buf_misc.c
OBJ = $(SRCS:.c=.o)
TEST_BIN = tests/test_world
HUD_TEST_BIN = tests/test_hud
INPUT_TEST_BIN = tests/test_input
CAMERA_TEST_BIN = tests/test_camera
HUD_TEST_SRCS = tests/test_hud.c srcs/hud_buf_core.c srcs/hud_buf_misc.c \
	srcs/hud_help.c srcs/hud_mouse.c srcs/hud_status_panel.c \
	srcs/hud_status_text.c srcs/input_core2.c srcs/image_utils.c \
	srcs/font5_port_gol.c $(wildcard srcs/mlx_font/*.c)

VALID = \033[1;32m
NOTVALID = \033[1;31m
INFOS = \033[1;36m
RESET = \033[0m

MLX_LINK = https://github.com/42paris/minilibx-linux.git
LIBFT_LINK = git@github.com:Matisse-Krn/libft.git
# The versions in the last known stable release: avoid silent dependency drift.
MLX_REV = f07d00f07c5c652223f505b526f84dab73cf2598
LIBFT_REV = f9f9db785d79b99e45635bdfc23e72b3c37874a0

.PHONY: all test DL_MLX MLX DL_LIBFT clean_mlx clean fclean aclean re rr listC listNb norm
all: $(NAME)

mlx_linux/Makefile:
	@printf "$(VALID)Downloading MiniLibX from $(MLX_LINK)\n$(RESET)"
	@git clone $(MLX_LINK) mlx_linux
	@git -C mlx_linux checkout --detach $(MLX_REV)

mlx_linux/libmlx_Linux.a: mlx_linux/Makefile $(wildcard mlx_linux/*.[ch])
	@printf "$(VALID)Building MiniLibX\n$(RESET)"
	@$(MAKE) -C mlx_linux > /dev/null

DL_MLX: mlx_linux/Makefile
MLX: mlx_linux/libmlx_Linux.a

libft/Makefile:
	@printf "$(VALID)Downloading libft from $(LIBFT_LINK)\n$(RESET)"
	@git clone $(LIBFT_LINK) libft
	@git -C libft checkout --detach $(LIBFT_REV)

libft/libft.a: libft/Makefile $(wildcard libft/*.[ch] libft/includes/*.h)
	@printf "$(VALID)Building libft\n$(RESET)"
	@$(MAKE) -C libft FLAGS="$(CSTD) -Wall -Wextra -Werror" > /dev/null

DL_LIBFT: libft/Makefile

# Parallel builds must fetch both sets of headers before compiling our sources.
$(OBJ): Makefile | mlx_linux/Makefile libft/Makefile

%.o: %.c
	@$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJ) mlx_linux/libmlx_Linux.a libft/libft.a
	@printf "$(INFOS)C standard: $(CSTD)\nCompiler flags: $(CFLAGS)\n$(RESET)"
	@$(CC) $(CSTD) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@printf "$(VALID)Compilation done: ./$(NAME)\n$(RESET)"

# Headless simulation tests: no X11 display or development headers required.
$(TEST_BIN): tests/test_world.c srcs/compute_step.c srcs/init_world.c srcs/time.c libft/libft.a Makefile | mlx_linux/Makefile
	@$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) tests/test_world.c \
		srcs/compute_step.c srcs/init_world.c srcs/time.c \
		libft/libft.a -lm -o $(TEST_BIN)

$(HUD_TEST_BIN): $(HUD_TEST_SRCS) libft/libft.a Makefile | mlx_linux/Makefile
	@$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) $(HUD_TEST_SRCS) \
		libft/libft.a -o $(HUD_TEST_BIN)

$(INPUT_TEST_BIN): tests/test_input.c srcs/input_keyboard.c srcs/input_key_actions.c srcs/input_core2.c Makefile | mlx_linux/Makefile libft/Makefile
	@$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) tests/test_input.c \
		srcs/input_keyboard.c srcs/input_key_actions.c srcs/input_core2.c \
		-o $(INPUT_TEST_BIN)

$(CAMERA_TEST_BIN): tests/test_camera.c srcs/input_camera.c srcs/camera_view.c srcs/camera_view_utils.c Makefile | mlx_linux/Makefile libft/Makefile
	@$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) tests/test_camera.c \
		srcs/input_camera.c srcs/camera_view.c srcs/camera_view_utils.c \
		-lm -o $(CAMERA_TEST_BIN)

test: $(TEST_BIN) $(HUD_TEST_BIN) $(INPUT_TEST_BIN) $(CAMERA_TEST_BIN)
	@./$(TEST_BIN)
	@./$(HUD_TEST_BIN)
	@./$(INPUT_TEST_BIN)
	@./$(CAMERA_TEST_BIN)

clean_mlx:
	@printf "$(NOTVALID)Cleaning MiniLibX\n$(RESET)"
	+@if [ -f "mlx_linux/Makefile.gen" ]; then \
		$(MAKE) -C mlx_linux clean > /dev/null; \
	fi

clean: clean_mlx
	@printf "$(NOTVALID)Cleaning libft and object files\n$(RESET)"
	+@if [ -f "libft/Makefile" ]; then \
		$(MAKE) -C libft clean > /dev/null; \
	fi
	@rm -f $(OBJ) $(OBJ:.o=.d)

fclean: clean
	@rm -f $(NAME) $(TEST_BIN) $(HUD_TEST_BIN) $(INPUT_TEST_BIN) \
		$(CAMERA_TEST_BIN) libft/libft.a

# Explicitly requested full dependency removal, never part of ordinary clean.
aclean: fclean
	@rm -rf mlx_linux libft

re:
	@$(MAKE) fclean
	@$(MAKE) all

rr:
	@$(MAKE) aclean
	@$(MAKE) all

listC:
	@LIST=$$(find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' '); \
	printf "All .c sources files copied into clipboard:\n$$LIST\n"; \
	echo -n $$LIST | xclip -selection clipboard

listNb:
	@echo "Number of .c files :"
	@find -wholename "./srcs/*.c" | wc -l

norm:
	@norminette ./srcs ./includes ./libft

-include $(OBJ:.o=.d)
