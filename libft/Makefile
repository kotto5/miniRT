NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DFLAGS = -MMD -MP

SRCDIR = srcs
SRCS = \
$(SRCDIR)/ft_isalnum.c\
$(SRCDIR)/ft_isalpha.c\
$(SRCDIR)/ft_isascii.c\
$(SRCDIR)/ft_isdigit.c\
$(SRCDIR)/ft_isprint.c\
$(SRCDIR)/ft_isdigit_str.c\
$(SRCDIR)/ft_isdouble.c\
$(SRCDIR)/ft_strlen.c\
$(SRCDIR)/ft_memcpy.c\
$(SRCDIR)/ft_memset.c\
$(SRCDIR)/ft_bzero.c\
$(SRCDIR)/ft_memmove.c\
$(SRCDIR)/ft_strlcpy.c\
$(SRCDIR)/ft_strlcat.c\
$(SRCDIR)/ft_calloc.c\
$(SRCDIR)/ft_atoi.c\
$(SRCDIR)/ft_atof.c\
$(SRCDIR)/ft_itoa.c\
$(SRCDIR)/ft_memchr.c\
$(SRCDIR)/ft_memcmp.c\
$(SRCDIR)/ft_putchar_fd.c\
$(SRCDIR)/ft_putendl_fd.c\
$(SRCDIR)/ft_putnbr_fd.c\
$(SRCDIR)/ft_putstr_fd.c\
$(SRCDIR)/ft_split.c\
$(SRCDIR)/ft_strchr.c\
$(SRCDIR)/ft_strdup.c\
$(SRCDIR)/ft_striteri.c\
$(SRCDIR)/ft_strjoin.c\
$(SRCDIR)/ft_strmapi.c\
$(SRCDIR)/ft_strncmp.c\
$(SRCDIR)/ft_strnstr.c\
$(SRCDIR)/ft_strrchr.c\
$(SRCDIR)/ft_strtrim.c\
$(SRCDIR)/ft_substr.c\
$(SRCDIR)/ft_tolower.c\
$(SRCDIR)/ft_toupper.c\
$(SRCDIR)/ft_print_system.c\
$(SRCDIR)/ft_print_system2.c\
$(SRCDIR)/ft_printf.c\
$(SRCDIR)/ft_dlstnew.c\
$(SRCDIR)/ft_dlsthead.c\
$(SRCDIR)/ft_dlstlast.c\
$(SRCDIR)/ft_dlstadd_back.c\
$(SRCDIR)/ft_dlstadd_front.c\
$(SRCDIR)/ft_dlstclear.c\
$(SRCDIR)/ft_dlstdelone.c\
$(SRCDIR)/ft_dlstsearch.c\
$(SRCDIR)/ft_dlstdelete.c\
$(SRCDIR)/ft_lstnew.c\
$(SRCDIR)/ft_lstadd_front.c\
$(SRCDIR)/ft_lstsize.c\
$(SRCDIR)/ft_lstlast.c\
$(SRCDIR)/ft_lstadd_back.c\
$(SRCDIR)/ft_lstdelone.c\
$(SRCDIR)/ft_lstclear.c\
$(SRCDIR)/ft_lstiter.c\
$(SRCDIR)/ft_lstmap.c\
$(SRCDIR)/ft_strtol.c\
$(SRCDIR)/ft_galloc.c\
$(SRCDIR)/ft_treenew.c\
$(SRCDIR)/get_next_line_bonus.c\
$(SRCDIR)/get_next_line_utils_bonus.c\
$(SRCDIR)/gc_malloc.c\
$(SRCDIR)/ft_free_double_ptr.c\
$(SRCDIR)/ft_get_size_double_ptr.c\

INCLUDES = -Iincludes
OBJDIR = obj
OBJS		:= $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:%.c=%.o))
DEPENDS		:= $(patsubst $(SRCDIR)%, $(OBJDIR)/%, $(SRCS:%.c=%.d))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

all:$(NAME)

$(NAME):$(OBJS)
	ar r $(NAME) $(OBJS)

.PHONY:
	clean;

clean:
	rm -f $(OBJS) $(DEPENDS)

fclean:clean
	rm -f $(NAME)

re:fclean all

-include $(DEPENDS)

