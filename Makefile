NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror
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

$(LIBFT):
	make -C ./libft

$(LIBMLX):
	make -C ./minilibx

clean:
	rm -f $(OBJ)
	make clean -C ./libft
	make clean -C ./minilibx

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
