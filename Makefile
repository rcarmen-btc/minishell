# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#              #
#    Updated: 2021/07/10 19:29:25 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBS = -L./src/libft -lft

CC = gcc
FLAGS = -g -Wall -Werror -Wextra -pipe 

INC_DIRS = inc/ src/libft/inc/

SRCS = main.c free_and_exit.c get_path_to_exe.c init.c strjoin.c error.c
SRCS_DIR = src/

OBJS = $(patsubst %.c, %.o, $(SRCS))
OBJS_DIR = od/

PATH_TO_SRCS = $(addprefix $(SRCS_DIR), $(SRCS))

PATH_TO_OBJS = $(addprefix $(OBJS_DIR), $(OBJS))

D_PATH = $(patsubst %.o, %.d, $(PATH_TO_OBJS))

all: od $(NAME)

$(NAME): $(PATH_TO_OBJS)
	@$(MAKE) -C src/libft
	$(CC) $^ -o $(NAME) $(LIBS)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32mSuccessfully compiled pipex\033[0m"

include	$(wildcard $(D_PATH))

VPATH = $(SRCS_DIR)

$(OBJS_DIR)%.o: %.c $(INC_DIRS)
	gcc -c -MD $(FLAGS) $< -o $@ -MD $(addprefix -I, $(INC_DIRS))
	@echo "\033[90m[\033[32mOK\033[90m]\033[33mCompiling $<\033[0m"

od:
	mkdir -p od/

clean:
	@$(MAKE) clean -C src/libft
	rm -rf od/

fclean: clean
	@$(MAKE) fclean -C src/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
