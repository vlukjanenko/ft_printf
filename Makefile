# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2019/11/18 14:25:28 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
HEADER = ft_printf.h
INCLUDES = lib/
COMPILERC = gcc
FLAGS = -g #-Wall -Wextra -Werror
SOURCES  =  ft_printf.c ft_lstp2back.c
LIB = libft/ft_*.c libft/libft.h libft/libft.a
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	$(COMPILERC) -o $(NAME) $(OBJECTS) -I $(INCLUDES) -L libft/ -lft

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