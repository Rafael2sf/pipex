# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 10:56:28 by rafernan          #+#    #+#              #
#    Updated: 2021/12/16 16:28:53 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	=		pipex

################ TERMINAL ###############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp

################# COLORS ################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################# DIRS ##################

_SRC	=		src/
_OBJ	=		obj/
_LIB	=		libs/
_BIN	=		bin/

############### COMPILER ################

CC		=		gcc
CF		=		-Wall -Werror -Wextra

################ FILES ##################

SRCS	=		$(_SRC)main.c
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
DEPS	=		libft.a libpx.a
LIBS	=		-lft -lpx

SRCS_B	=		$(_SRC)main_bonus.c
OBJS_B	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS_B))
DEPS_B	=		libft.a libpx_bonus.a
LIBS_B	=		-lft -lpx_bonus

################ RULES ##################

all: deps $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CF) -c $< -o $@

$(NAME): deps $(OBJS)
	$(CC) $(CF) $(LIBS) $(OBJS) -o $@ -L $(_LIB)

bonus: deps_b $(OBJS_B)
	$(CC) $(CF) $(LIBS_B) $(OBJS_B) -o $(NAME) -L $(_LIB)

################ DEPS ###################

deps: $(DEPS)

libft.a:
	$(MKE) libft.a -C src/libft/

libpx.a:
	$(MKE) libpx.a -C src/libpx/

deps_b: $(DEPS_B)

libpx_bonus.a:
	$(MKE) libpx_bonus.a -C src/libpx/

############## STRUCTURE ################

$(_OBJ):
	$(MKD) $(_OBJ)

$(_LIB):
	$(MKD) $(_LIB)

$(_SRC):
	$(MKD) $(_SRC)

$(_BIN):
	$(MKD) $(_BIN)

################### CLEAN ###############

clean:
	$(RMV) -r $(_OBJ) $(_LIB)

fclean: clean
	$(RMV) -r $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
