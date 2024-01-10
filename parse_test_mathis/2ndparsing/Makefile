# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 21:42:07 by mafranco          #+#    #+#              #
#    Updated: 2024/01/10 22:17:14 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc
RM	=	rm -f

CFLAGS	=	-Werror -Wall -Wextra
LIBFLAGS	=	-lreadline -L./libft -lft

SRC	=	src/minishell.c	src/get_path.c src/split_input.c \
		src/exec_funcion.c src/ft_echo.c src/ft_cd.c src/ft_pwd.c \
		src/ft_export.c src/ft_unset.c src/ft_env.c src/ft_exit.c \
		src/ft_dollar_sign.c src/ft_execve.c

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
	#mv src/*.o .obj/

clean:
	$(RM) .obj/*.o
	$(RM) src/*.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: libft all clean fclean re
