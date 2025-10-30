NAME = get_next_line.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=1024

SRCS = get_next_line.c 

OBJS = $(SRCS:.c=.o)

HEADERS = get_next_line.h

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rc $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re