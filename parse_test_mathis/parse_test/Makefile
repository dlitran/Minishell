# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 21:42:07 by mafranco          #+#    #+#              #
#    Updated: 2023/11/28 19:47:13 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc
RM	=	rm -f

CFLAGS	=	-Werror -Wall -Wextra
LIBFLAGS	=	-lreadline -L./libft -lft

SRC	=	src/minishell.c src/free.c src/utils.c src/max_split.c \
		src/ft_function.c
LIB	=	header.h
LIBFT_PATH	=	libft

OBJ	=	$(SRC:.c=.o)

%.o:	%.c $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

lib:
	make -C $(LIBFT_PATH)

$(NAME): lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFLAGS) -o $@
	mv src/*.o .obj/

clean:
	$(RM) .obj/*.o
	$(RM) src/*.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: libft all clean fclean re
