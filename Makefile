# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 16:04:38 by majosue           #+#    #+#              #
#    Updated: 2021/11/07 23:21:39 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
PATH_TO_LIBFT = ./libft
COMPILERC = gcc
MAKE_LIB = ar rcs
FLAGS = -Wall -Wextra -Werror
HEADERS = ./includes/ft_printf.h $(PATH_TO_LIBFT)/includes/libft.h
HEADERS_PATHS = ./includes/ $(PATH_TO_LIBFT)/includes/
OBJECTS_DIRECTORY = ./objects/
SOURCES_DIRECTORY = ./sources/
INCLUDES = $(addprefix -I , $(HEADERS_PATHS))
SOURCES = \
	ft_chkflags.c   ft_fmt_width.c  ft_get_size.c   ft_lstp2back.c \
	ft_number_x.c   ft_readformat.c ft_fmt_prec.c   ft_ftoa.c \
	ft_itoa_base.c  ft_number.c     ft_printf.c     ft_string.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_DIRECTORY), $(SOURCES))

.PHONY: all clean fclean re

all:  $(OBJECTS_DIRECTORY) $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE_LIB) $(NAME) $?

$(OBJECTS) : $(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(COMPILERC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

clean:
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(NAME)

re: fclean all
