NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
DFLAGS = -MMD -MP

SRCDIR = srcs
SRCS =		$(SRCDIR)/affine_rotation.c \
			$(SRCDIR)/bright_color_clc1.c \
			$(SRCDIR)/color_img.c \
			$(SRCDIR)/conf_validation.c \
			$(SRCDIR)/fmt_checker_camera.c \
			$(SRCDIR)/fmt_checker_cylinder.c \
			$(SRCDIR)/fmt_checker_light.c \
			$(SRCDIR)/fmt_checker_plane.c \
			$(SRCDIR)/fmt_checker_sphere.c \
			$(SRCDIR)/fmt_checker_cone.c \
			$(SRCDIR)/get_color_with_at.c \
			$(SRCDIR)/get_from_split.c \
			$(SRCDIR)/get_lights.c \
			$(SRCDIR)/get_objects.c \
			$(SRCDIR)/get_ref.c \
			$(SRCDIR)/has_valid_format.c \
			$(SRCDIR)/identifers.c \
			$(SRCDIR)/img_color_clc1.c \
			$(SRCDIR)/is_valid_contens.c \
			$(SRCDIR)/is_valid_orientation_vector.c \
			$(SRCDIR)/is_valid_rgb_in_range.c \
			$(SRCDIR)/lightsource.c \
			$(SRCDIR)/lightsource_spotlight.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/make_instance.c \
			$(SRCDIR)/new_obj.c \
			$(SRCDIR)/obj_cylinder.c \
			$(SRCDIR)/obj_plane.c \
			$(SRCDIR)/obj_rect.c \
			$(SRCDIR)/obj_sphere.c \
			$(SRCDIR)/obj_cone.c \
			$(SRCDIR)/parse_file.c \
			$(SRCDIR)/parse_line.c \
			$(SRCDIR)/put_error.c \
			$(SRCDIR)/set_event.c \
			$(SRCDIR)/set_rotation_matrix.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/utils2.c \
			$(SRCDIR)/vec_clc1.c \
			$(SRCDIR)/vec_clc2.c \
			$(SRCDIR)/vec_clc3.c \
			$(SRCDIR)/vec_clc4.c

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
