# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/09/17 17:31:27 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = libft.h main.h token.h lexer.h execute.h builtins.h
INC = src/libft/inc/libft.h inc/main.h

LIBS = -L./src/libft -lft -lreadline

OUTFILE = test/mout

SRC = builtins.c         execute_sheesh.c  lexer.c        print_lst.c \
		builtins_dirs.c  execute_wtf.c     lexer_ijk.c    signals.c \
		builtins_env.c   expand.c          lexer_wtf.c    token.c \
		execute.c        get_idk.c         tokenlst.c \
		execute_idk.c    get_ijk.c         main.c \
		execute_ijk.c    get_wtf.c         pipelinelst.c

OBJ =	$(patsubst %.c, %.o, $(SRC))

INC_DIR = inc/ src/libft/inc
SRC_DIR = src/
OBJ_DIR = od/

SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))
OBJ_PATH = $(addprefix $(OBJ_DIR), $(OBJ))
D_PATH = $(patsubst %.o, %.d, $(OBJ_PATH))

CC = clang
CFLAGS = -Wall -Wextra -Werror
OPT_FLUGS = -O0 -g3 -pipe

HMM_COLOR   = \033[1;95m
COM_COLOR   = \033[1;94m
OBJ_COLOR   = \033[1;96m
OK_COLOR    = \033[1;92m
ERROR_COLOR = \033[1;91m
WARN_COLOR  = \033[1;93m
NO_COLOR    = \033[0m

SYAN_COLOR = \e[1;96m
YELLOW_COLOR = \e[1;93m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

define run
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all: od $(NAME)

$(NAME): $(OBJ_PATH) 
	@$(MAKE) all -C src/libft/
	@$(CC) $^ -o $(NAME) $(LIBS)
	@echo "$(OK_COLOR)----SUCCSESS MINISHELL----$(NO_COLOR)"

VPATH = $(SRC_DIR)

$(OBJ_DIR)%.o: %.c
	@$(call run, $(CC) $(CFLAGS) $(OPT_FLUGS) -c $< -o $@ $(addprefix -I, $(INC_DIR)))
	
od:
	@mkdir -p od/

clean:
	@if [ -e $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR);	\
  		printf "%-60b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(OBJ_DIR)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	else \
  		printf "%-41b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(OBJ_DIR)" "$(ERROR_COLOR)[There is no such directory]$(NO_COLOR)\n"; \
	fi;

fclean: clean
	@if [ -e $(NAME) ]; then \
		$(MAKE) fclean -C src/libft; \
		rm -f $(NAME); \
  		printf "%-60b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	else \
  		printf "%-41b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(ERROR_COLOR)[There is no such file]$(NO_COLOR)\n"; \
	fi;

re: fclean all

test_clean:
	@rm -f test/bash_out test/my_out

.PHONY: all clean fclean re
