NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iget_next_line -Iincludes

OBJDIR = .obj
GITLIBFT = git@github.com:BahaBerkPancar/Libft-42.git
LIBFT = libft/libft.a
GNL = get_next_line/get_next_line.a

SRCS = main.c read_header.c rgbs.c \
	checks/checks.c checks/check_textures.c \
	utils/print.c utils/free.c utils/utils.c utils/ext.c \
	map_handle/read_map.c map_handle/flood_fill.c map_handle/map_checks.c \
	mlx_files/mlx_keys.c mlx_files/mlx_utils.c mlx_files/minimap.c mlx_files/mlx.c \
	player/player.c player/movements.c player/movements_2.c \

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

MLX_DIR = minilibx_opengl_20191021
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLACK = \033[0;30m
COLOR_BOLD_RED = \033[1;31m

all: check_dir $(NAME)

check_dir:
	@if [ ! -d "libft" ]; then \
		clear; \
		echo "$(COLOR_RED)You need to clone libft! ❌"; \
		echo "$(COLOR_YELLOW) Running 'make clone'"; \
		$(MAKE) clone;\
	fi

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(GNL):
	@$(MAKE) -C get_next_line

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(MLX_DIR)/libmlx.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME)
	@echo "$(COLOR_BLACK)@ DONE $(NAME) ✅$(COLOR_RESET)"

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C libft > /dev/null 2>&1
	@if [ -d "get_next_line" ]; then $(MAKE) clean -C get_next_line > /dev/null 2>&1; fi
	@echo "$(COLOR_RED)@ Cleaned All Objects$(COLOR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED)@ Cleaned $(NAME)$(COLOR_RESET)"

re: fclean all

clone:
	@echo "$(COLOR_GREEN)@ Cloning libft...$(COLOR_RESET)"
	@git clone $(GITLIBFT) libft
	@$(MAKE) -C libft > /dev/null 2>&1
	@$(MAKE) bonus -C libft > /dev/null 2>&1
	@echo "$(COLOR_GREEN)@ Cloned libft ✅$(COLOR_RESET)"

full-clean: fclean
	@rm -rf libft
	@echo "$(COLOR_BOLD_RED)🌀 You Have Cleared Everything$(COLOR_RESET)"

run: all
	@./$(NAME) a.cub || true

.PHONY: all clean fclean re clone run
