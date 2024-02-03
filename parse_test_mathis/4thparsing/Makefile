# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:22:34 by mafranco          #+#    #+#              #
#    Updated: 2024/02/03 17:18:48 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra
LIBFLAGS	=	-L/usr/local/opt/readline/lib -lreadline -L./libft -lft
COMFLAGS	= -I/usr/local/opt/readline/include

SRC	=	src/minishell.c src/ft_getenv.c src/error_manager.c \
		src/free_data.c src/quotes.c src/ft_parse_input.c \
		src/utils.c src/pipe.c src/utils_parse.c src/redir.c \
		src/ft_no_pipe.c src/ft_with_pipe.c src/utils_execution.c\
		src/ft_find_funcion.c src/ft_cd.c src/ft_dollar_sign.c \
		src/ft_echo.c src/ft_env.c src/ft_execve.c src/ft_exit.c \
		src/ft_export.c src/ft_pwd.c src/ft_unset.c src/ft_exec_pipe.c\
		src/ft_signal.c

LIB	=	header.h
LIBFT_PATH	=	libft

OBJ	=	$(SRC:.c=.o)

%.o:	%.c $(LIB)
	$(CC) $(CFLAGS) $(COMFLAGS) -c $< -o $@

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
