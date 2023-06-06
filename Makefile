NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
DFLAGS = -MMD -MP

SRCDIR = srcs
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJDIR = ./objs
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

OBJ := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPENDS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.d))

# for online
# mac
# LIBXDIR = ./minilibx
# LIBMLX = ./minilibx/libmlx.a
# LIBMLXFLAGS = -framework OpenGL -framework AppKit

# linux
# LIBXDIR = ./minilibx-linux
# LIBMLX = $(LIBXDIR)/libmlx.a
# LIBMLXFLAGS = -lXext -lX11
# CFLAGS += -lm

# for online
# INCLUDES = -I./includes -I./libft/includes -I./minilibx-linux

# for offline
INCLUDES = -I./includes -I./libft/includes

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

# for online
# $(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(INCLUDES) $(LIBMLXFLAGS) -lm -o $@

# for offline
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -L/usr/X11R6/lib -lmlx -lX11 -lXext -framework OpenGL -framework AppKit -o $@

$(LIBFT): FORCE
	make -C ./$(LIBFTDIR)

FORCE:

# for online
# $(LIBMLX):
# 	make -C $(LIBXDIR)

clean:
	rm -f $(OBJ) $(DEPENDS)
	make clean -C $(LIBFTDIR)

# for online
# clean:
# 	rm -f $(OBJ) $(DEPENDS)
# 	make clean -C $(LIBFTDIR)
# 	make clean -C $(LIBXDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

NAME_DEBUG = debugfile
CFLAGS_DEBUG = -g

$(NAME_DEBUG): $(LIBFT) $(LIBMLX) $(OBJ)
	@printf "$(GREEN)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -L/usr/X11R6/lib -lmlx -lX11 -lXext -framework OpenGL -framework AppKi -o $@
	@printf "$(RESET)"

# for online
# $(NAME_DEBUG): $(LIBFT) $(LIBMLX) $(OBJ)
# 	@printf "$(GREEN)"
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(INCLUDES) $(LIBMLXFLAGS) -lm -o $@
# 	@printf "$(RESET)"

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re FORCE

norm:
	norminette

-include $(DEPENDS)
