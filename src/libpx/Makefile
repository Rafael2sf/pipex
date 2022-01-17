# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 10:54:19 by rafernan          #+#    #+#              #
#    Updated: 2021/12/17 14:22:29 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############# STATIC LIBRARY ############

NAME	=		libpx.a
NAME_B	=		libpx_bonus.a

################### TERMINAL ############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp

################### COLORS ##############

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################### DIRS ################

_SRC	=
_OBJ	=		../../obj/
_LIB	=		../../libs/
_BIN	=		../../bin/

################### COMPILER ############

CC		=		gcc
AR		=		ar rcs
CF		=		-g -Wall -Werror -Wextra

################### FILES ###############

SRCS_	=		exec.c \
				matrix.c \
				ncmd.c \
				pipex.c \
				struct.c \
				utils.c

SRCS	=		$(addprefix $(_SRC), $(SRCS_))
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))

SRCS__B	=		exec.c \
				matrix.c \
				ncmd.c \
				utils.c \
				pipex_bonus.c \
				struct_bonus.c \
				hdoc_bonus.c

SRCS_B	=		$(addprefix $(_SRC), $(SRCS__B))
OBJS_B	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS_B))

################### RULES ###############

all: $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CF) -c $< -o $@

$(NAME): $(_LIB) $(_LIB)$(NAME)
$(_LIB)$(NAME): $(_OBJ) $(OBJS)
	$(AR) $@ $(OBJS)

bonus: $(NAME_B)

$(NAME_B): $(_LIB) $(_LIB)$(NAME_B)
$(_LIB)$(NAME_B): $(_OBJ) $(OBJS_B)
	$(AR) $@ $(OBJS_B)

################### STRUCTURE ###########

$(_OBJ):
	$(MKD) $@

$(_LIB):
	$(MKD) $@

$(_SRC):
	$(MKD) $@

################### CLEAN ###############

clean:
	$(RMV) $(OBJS) $(OBJS_B) 

fclean: clean
	$(RMV) $(_LIB)$(NAME)

re: fclean all

.PHONY: all bonus clean fclean re