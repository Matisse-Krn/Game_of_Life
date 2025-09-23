CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g3 -march=native -flto
NAME = game_of_life
SRCS = srcs/compute_step.c srcs/init.c srcs/time.c srcs/world_draw.c srcs/init_world.c srcs/image_utils.c srcs/init_mlx.c srcs/input_core.c srcs/clip_fill.c srcs/destroy.c srcs/main.c srcs/init_view.c
OBJ = $(SRCS:.c=.o)
LIB_PATH = -Lmlx_linux -Llibft -L/usr/lib
LIB_NAME = -lmlx_Linux -lft -lXext -lX11 -lm -lz
INCLUDE_PATH = -I/usr/include -Imlx_linux -Ilibft/includes -Iincludes

VALID = \033[1;32m
NOTVALID = \033[1;31m
LOADING = \033[1;33m
INFOS = \033[1;36m
RESET = \033[0m

MLX_LINK = https://github.com/42paris/minilibx-linux.git
LIBFT_LINK = git@github.com:Matisse-Krn/libft.git

.PHONY : all
all: MLX libft/libft.a $(NAME)

DL_MLX:
	@if [ ! -d "mlx_linux" ]; then \
        printf "$(VALID)⇩ Downloading and extracting MiniLibX (from $(MLX_LINK))...\n$(LOADING)"; \
        git clone $(MLX_LINK) mlx_linux >> /dev/null; \
		printf "$(RESET)";\
    else \
        echo "✅ $(VALID)mlx-linux already downloaded.$(RESET)"; \
    fi

MLX: DL_MLX
	@printf "$(VALID)⇩ Make MLX\n$(RESET)";
	@$(MAKE) -C mlx_linux > /dev/null 2>&1

DL_LIBFT:
	@if [ ! -d "libft" -o ! -f "libft/Makefile" ]; then \
		printf "$(VALID)⇩ Downloading libft (from $(LIBFT_LINK))\n$(LOADING)"; \
		git clone $(LIBFT_LINK) libft >> /dev/null; \
		printf "$(RESET)"; \
	else \
		echo "✅ $(VALID)libft already downloaded.$(RESET)"; \
	fi

libft/libft.a: DL_LIBFT
	@printf "$(VALID)⇩ Make Libft\n$(RESET)";
	@$(MAKE) -C libft > /dev/null 2>&1

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE_PATH) -MMD -O3 -c $< -o $@
$(NAME): $(OBJ)
	@echo "$(INFOS)Flags =		$(FLAGS)\nIncludes =	$(INCLUDE_PATH)\nObj =		$(OBJ)\nLib =		$(LIB_NAME)$(RESET)\n";
	@$(CC) $(FLAGS) $(OBJ) $(LIB_PATH) $(LIB_NAME) $(INCLUDE_PATH) -o $(NAME);
	@echo "\n✅ $(VALID)Compilation done !$(RESET)\n"

.PHONY : clean_mlx
clean_mlx:
	@printf "$(NOTVALID)Cleanning MLX \n$(RESET)";
	@rm -rf minilibx-linux.tgz

.PHONY : clean
clean: clean_mlx
	@printf "$(NOTVALID)Cleanning LIBFT \n$(RESET)";
	@if [ -f "libft/Makefile" ]; then \
		$(MAKE) -C libft clean > /dev/null 2>&1;\
	fi
	@printf "$(NOTVALID)Remove *.o and *.d \n$(RESET)";
	@rm -rf $(OBJ) $(OBJ:.o=.d)

.PHONY : fclean
fclean: clean
	@printf "$(NOTVALID)Remove executable && libft.a\n$(RESET)";
	@rm -rf $(NAME) libft/libft.a

.PHONY : aclean
aclean: fclean
	@printf "$(NOTVALID)Remove mlx_linux and libft repertories\n$(RESET)";
	@rm -rf mlx_linux libft

.PHONY : re
re : fclean all

.PHONY : rr
rr: aclean all

.PHONY : listC
listC:
	@LIST=$$(find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' '); \
	printf "🗅 $(INFOS)All .c sources files copied into clipboard :\n$(RESET)$$LIST\n"; \
	echo -n $$LIST | xclip -selection clipboard

.PHONY : listNb
listNb:
	@echo "Number of .c files :" 
	@find -wholename "./srcs/*.c" | wc -l

.PHONY : norm
norm:
	@norminette ./srcs ./includes ./libft

-include $(OBJ:.o=.d)
