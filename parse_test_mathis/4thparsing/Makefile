# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:22:34 by mafranco          #+#    #+#              #
#    Updated: 2024/01/17 00:40:19 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra
LIBFLAGS	=	-lreadline -L./libft -lft


SRC	=	src/minishell.c src/ft_getenv.c src/error_manager.c \
		src/free_data.c src/quotes.c src/ft_parse_input.c \
		src/utils.c src/pipe.c src/utils_parse.c src/redir.c \

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

clean:
	rm -f src/*.o

fclean:	clean
	rm $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: libft all clean fclean re
