# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#              #
#    Updated: 2021/07/05 12:49:14 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INC_DIR = include src/libft/inc
INC = include/main.h src/libft/inc/libft.h

SRC = main.c free_and_exit.c get_path_to_exe.c 
SRC_DIR = src

LIBFT = src/libft/libft.a

ALL_SRC = $(addprefix $(SRC_DIR)/, $(SRC))

CC = gcc

FLAGS = -g -O0 -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(ALL_SRC) $(INC)
	@$(MAKE) -C src/libft
	$(CC) $(FLAGS) $(ALL_SRC) $(addprefix -I, $(INC_DIR)) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C src/libft

fclean:
	$(MAKE) fclean -C src/libft
	rm -f $(NAME)

execlean:
	rm -f $(NAME)

re: fclean all
