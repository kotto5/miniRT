NAME = miniRT
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# CFLAGS = -Wall -fsanitize=address
CFLAGS = -Wall
SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)
INCLUDES = -I./includes -Ilibft/
LIBFT = ./libft/libft.a
LIBMLX = ./minilibx/libmlx.a
LIBMLXFLAGS = -framework OpenGL -framework AppKit

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBMLXFLAGS) $^ -o $@

$(LIBFT): FORCE
	make -C ./libft

FORCE:

$(LIBMLX):
	make -C ./minilibx

clean:
	rm -f $(OBJ)
	make clean -C ./libft
	make clean -C ./minilibx

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

NAME_DEBUG = debugfile
CFLAGS_DEBUG = -g

$(NAME_DEBUG): $(LIBFT) $(LIBMLX) $(OBJ)
	@printf "$(GREEN)"
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBMLXFLAGS) $^ -o $@
	@printf "$(RESET)"

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re FORCE

norm:
	norminette