# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 16:22:45 by shtanemu          #+#    #+#              #
#    Updated: 2023/04/24 17:42:39 by shtanemu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
CC := cc
RM := rm -f
CFLAGS := -Wall -Wextra -Werror -MMD

SRCDIR := srcs
SRCS := main.c

OBJDIR := objs
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR    = .
endif
# OBJS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCDIR)/$(SRCS:%.c=%.o))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
DEPENDS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.d))
-include $(DEPENDS)

MINILIBXDIR := minilibxmms20200219/

INCDIR := include/
# INCLUDE := -I$(INCDIR) -I$(MINILIBXDIR)
INCLUDE := -I$(INCDIR)

all: $(NAME)

clean: 
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE) -lmlx -framework OpenGL -framework AppKit

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -Imlx -c $< -o $@

.PHONY: all clean fclean re
