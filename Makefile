NAME = cub3D
CC = cc
CFLAGS =  -Wall -Wextra -Werror -Ilibft -Iget_next_line 

INCLUDES = -Iincludes

OBJDIR = .obj
GITLIBFT = git@github.com:BahaBerkPancar/Libft-42.git
LIBFT = libft/libft.a
GNL = get_next_line/get_next_line.a

SRCS = main.c read_header.c  rgbs.c   \
	checks/checks.c checks/check_textures.c \
	utils/print.c utils/free.c utils/utils.c utils/ext.c \
	map_handle/read_map.c map_handle/flood_fill.c map_handle/map_checks.c \

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

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
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(GNL):
	@$(MAKE) -C get_next_line

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(READLINEFLAGS) -o $(NAME)
	@echo "$(COLOR_BLACK)@ DONE $(NAME) ✅$(COLOR_RESET)"

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C libft > /dev/null 2>&1
	@if [ -d "get_next_line" ]; then $(MAKE) clean -C get_next_line > /dev/null 2>&1; fi
	@echo "$(COLOR_RED)@ Cleaned All Objects$(COLOR_RESET)"

clone:
	@echo "$(COLOR_GREEN)@ Cloning libft...$(COLOR_RESET)"
	@git clone $(GITLIBFT) libft
	@$(MAKE) -C libft > /dev/null 2>&1
	@$(MAKE) bonus -C libft > /dev/null 2>&1
	@echo "$(COLOR_GREEN)@ Cloned libft ✅$(COLOR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED)@ Cleaned $(NAME)$(COLOR_RESET)"

re: fclean all

full-clean: fclean
	@rm -rf libft
	@echo "$(COLOR_BOLD_RED)🌀 You Have Cleared Everything$(COLOR_RESET)"

run: all
	@./$(NAME) a.cub || true


.PHONY: all clean fclean re clone run