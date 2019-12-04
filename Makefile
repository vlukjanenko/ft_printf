# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2019/12/04 19:33:42 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
HEADER = ft_printf.h
INCLUDES = lib/
COMPILERC = gcc
MAKERLIB = ar rc
FLAGS = -g -Wall -Wextra -Werror
SOURCES  =  ft_printf.c ft_lstp2back.c ft_readformat.c ft_chkflags.c \
ft_gettab.c ft_get_f.c ft_add_left.c ft_add_right.c ft_shiftarg.c \
ft_null.c ft_space.c ft_minus.c ft_plus.c ft_skipflags.c ft_width.c \
ft_prec.c ft_char.c ft_fmt_char.c ft_percent.c ft_string.c \
ft_itoa_base.c ft_itoa_base_u.c ft_get_size.c ft_get_size_u.c ft_sharp.c \
ft_fmt_width.c ft_fmt_prec.c ft_number.c ft_number_o.c ft_number_x.c \
ft_number_u.c
LIB_O = libft/ft_*.o
LIB = libft/ft_*.c libft/libft.h libft/libft.a
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB) $(LIB_O)
	$(MAKERLIB) $(NAME) $(LIB_O) $(OBJECTS)
	ranlib $(NAME) 
# $(NAME): $(OBJECTS) $(LIB)
# 	$(COMPILERC) -o $(NAME) $(OBJECTS) -I $(INCLUDES) -L libft/ -lft

$(LIB_O):
	@make -C libft/

$(LIB): 
	@make -C libft/

%.o: %.c $(HEADER)
	$(COMPILERC) $(FLAGS) -o $@ -c $< 

clean:
	@rm -f $(OBJECTS)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all