# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/07/10 00:26:47 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = libft.h main.h
INC = src/libft/inc/libft.h inc/main.h
SRC = main.c
OBJ =	$(patsubst %.c, %.o, $(SRC))
LIBS = -L./src/libft -lft -lreadline

INC_DIR = inc/ src/libft/inc
SRC_DIR = src/
OBJ_DIR = od/

SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))
OBJ_PATH = $(addprefix $(OBJ_DIR), $(OBJ))
D_PATH = $(patsubst %.o, %.d, $(OBJ_PATH))

CC = clang
CFLAGS = #-Wall -Wextra -Werror
OPT_FLUGS = -O -g3 -pipe

HMM_COLOR   = \033[0;35m
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

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
	@$(CC) $^ -o $(NAME) $(LIBS)
	@echo "$(OK_COLOR)----SUCCSESS MINISHELL----$(NO_COLOR)"


VPATH = $(SRC_DIR)

$(OBJ_DIR)%.o: %.c
	@$(MAKE) all -C src/libft/
	@echo "$(HMM_COLOR)----MINISHELL----$(NO_COLOR)"
	@$(call run, $(CC) $(CFLAGS) $(OPT_FLUGS) -c $< -o $@ -MD $(addprefix -I, $(INC_DIR)))
	
include	$(wildcard $(D_PATH))

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

.PHONY: all clean fclean re