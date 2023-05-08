NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
DFLAGS = -MMD -MP

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

# mac
LIBXDIR = ./minilibx
LIBMLX = ./minilibx/libmlx.a
LIBMLXFLAGS = -framework OpenGL -framework AppKit

# linux
# LIBXDIR = ./minilibx-linux
# LIBMLX = $(LIBXDIR)/libmlx.a
# LIBMLXFLAGS = -lXext -lX11
# CFLAGS += -lm

INCLUDES = -I./includes -I./libft -I./minilibx-linux

DEPENDS    :=  $(SRCS:.c=.d)


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(INCLUDES) $(LIBMLXFLAGS) -lm -o $@

$(LIBFT): FORCE
	make -C ./$(LIBFTDIR)

FORCE:

$(LIBMLX):
	make -C $(LIBXDIR)

clean:
	rm -f $(OBJ) $(DEPENDS)
	make clean -C $(LIBFTDIR)
	make clean -C $(LIBXDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

NAME_DEBUG = debugfile
CFLAGS_DEBUG = -g

$(NAME_DEBUG): $(LIBFT) $(LIBMLX) $(OBJ)
	@printf "$(GREEN)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(INCLUDES) $(LIBMLXFLAGS) -lm -o $@
	@printf "$(RESET)"
# $(CC) $(CFLAGS) $(INCLUDES) $(LIBMLXFLAGS) $^ -lm -o $@

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re FORCE

norm:
	norminette

-include $(DEPENDS)
