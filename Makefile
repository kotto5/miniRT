NAME = miniRT
CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g 
# CFLAGS = -Wall -Wextra -Werror -g -Wshadow
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
DFLAGS = -MMD -MP

SRCDIR = srcs
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJDIR = ./objs
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

OBJ    :=  $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPENDS    :=  $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.d))


# mac
LIBXDIR = ./minilibx
LIBMLX = ./minilibx/libmlx.a
LIBMLXFLAGS = -framework OpenGL -framework AppKit

# linux
# LIBXDIR = ./minilibx-linux
# LIBMLX = $(LIBXDIR)/libmlx.a
# LIBMLXFLAGS = -lXext -lX11
# CFLAGS += -lm

INCLUDES = -I./includes -I./libft/includes -I./minilibx-linux

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-mkdir -p $(@D) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@ 

%.o: %.c
	-mkdir -p $(@D) 
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
