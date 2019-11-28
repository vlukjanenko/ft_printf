# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2019/11/28 11:01:17 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
HEADER = ft_printf.h
INCLUDES = lib/
COMPILERC = gcc
MAKERLIB = ar rc
FLAGS = -g -Wall -Wextra -Werror
SOURCES  =  ft_printf.c ft_lstp2back.c ft_readformat.c ft_chkflags.c \
ft_gettab.c ft_get_f.c ft_add_left.c ft_add_right.c ft_shiftarg.c
LIB_O = libft/ft_*.o
LIB = libft/ft_*.c libft/libft.h libft/libft.a
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	$(MAKERLIB) $(NAME) $(LIB_O) $(OBJECTS)
	ranlib $(NAME) 
# $(NAME): $(OBJECTS) $(LIB)
# 	$(COMPILERC) -o $(NAME) $(OBJECTS) -I $(INCLUDES) -L libft/ -lft

$(LIB):
	@make -C libft/

%.o: %.c $(HEADER)
	$(COMPILERC) $(FLAGS) -I $(INCLUDES) -o $@ -c $< 

clean:
	@rm -f $(OBJECTS)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all