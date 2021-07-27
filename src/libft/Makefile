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

NAME = libft.a

INC =	libft.h
SRC =	ft_atoi.c          ft_lstdelone.c   ft_putendl_fd.c  ft_strnstr.c \
		ft_bzero.c         ft_lstiter.c     ft_putnbr_fd.c   ft_strrchr.c \
		ft_calloc.c        ft_lstlast.c     ft_putstr_fd.c   ft_strtrim.c \
		ft_isalnum.c       ft_lstmap.c      ft_split.c       ft_substr.c \
		ft_isalpha.c       ft_lstnew.c      ft_strchr.c      ft_tolower.c \
		ft_isascii.c       ft_lstsize.c     ft_strcpy.c      ft_toupper.c \
		ft_isdigit.c       ft_memccpy.c     ft_strdup.c      get_next_line.c \
		ft_isprint.c       ft_memchr.c      ft_strjoin.c     to_del_lst.c \
		ft_isspace.c       ft_memcmp.c      ft_strlcat.c     to_get_lst.c \
		ft_itoa_base.c     ft_memcpy.c      ft_strlcpy.c     to_pop_lst.c \
		ft_itoa.c          ft_memdel.c      ft_strlen.c      to_push_lst.c \
		ft_lstadd_back.c   ft_memmove.c     ft_strmapi.c \
		ft_lstadd_front.c  ft_memset.c      ft_strncmp.c \
		ft_lstclear.c      ft_putchar_fd.c  ft_strnew.c

OBJ =	$(patsubst %.c, %.o, $(SRC))

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = od/

SRC_PATH =	$(addprefix $(SRC_DIR), $(SRC))
OBJ_PATH =	$(addprefix $(OBJ_DIR), $(OBJ))
D_PATH =	$(patsubst %.o, %.d, $(OBJ_PATH))

CC = clang
CFLAGS = -Wall -Wextra -Werror
OPT_FLUGS = -O -g3 -pipe

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
	@ar rcs $(NAME) $?

VPATH = $(SRC_DIR)

$(OBJ_DIR)%.o: %.c
	@$(call run, $(CC) $(CFLAGS) $(OPT_FLUGS) -c $< -o $@ -MD -I$(INC_DIR))
	
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
		rm -f $(NAME); \
  		printf "%-60b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	else \
  		printf "%-41b%b" "$(COM_COLOR)Deletion $(OBJ_COLOR)$(NAME)" "$(ERROR_COLOR)[There is no such file]$(NO_COLOR)\n"; \
	fi;

re: fclean all

.PHONY: all clean fclean re
