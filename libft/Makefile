NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

M_SRCS = \
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_isdigit_str.c\
ft_isdouble.c\
ft_strlen.c\
ft_memcpy.c\
ft_memset.c\
ft_bzero.c\
ft_memmove.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_calloc.c\
ft_atoi.c\
ft_atof.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_print_system.c\
ft_print_system2.c\
ft_printf.c\
ft_dlstnew.c\
ft_dlsthead.c\
ft_dlstlast.c\
ft_dlstadd_back.c\
ft_dlstadd_front.c\
ft_dlstclear.c\
ft_dlstdelone.c\
ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c\
ft_strtol.c\

M_OBJS = $(M_SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)

OBJS = $(M_OBJS)
ifdef WITH_BONUS
OBJS += $(B_OBJS)
endif

all:$(NAME)

$(NAME):$(OBJS)
	ar r $(NAME) $(OBJS)

.PHONY:
	clean;

bonus:
	make WITH_BONUS=1

clean:
	rm -f $(M_OBJS) $(B_OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all
