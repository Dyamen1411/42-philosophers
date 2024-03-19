# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amassias <amassias@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 23:28:51 by amassias          #+#    #+#              #
#    Updated: 2024/01/13 20:36:21 by amassias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COL_RED		=	\x1b[1;31m
COL_GREEN	=	\x1b[1;32m
COL_RESET	=	\x1b[1;0m

SRC_DIR := ./
OBJ_DIR	:=	build

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3
LFLAGS		=	-pthread

FILES		=				\
	utils					\
	main					\
	philo_init				\
	philo_destroy			\
	error					\
	philo_start				\
	philo_life				\
	philo_log				\
	philo_eat				\
	custom_sleep			\


SRCS		=	$(addsuffix .c,$(FILES))
OBJS		=	$(addsuffix .o,$(FILES))

NAME		=	philo

.PHONY: all bonus clean fclean re norminette

all: $(NAME)

bonus: all

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ -I. $(CFLAGS)

norminette:
	@norminette | grep -Ev '^Notice:|OK!$$'	\
	&& echo -e '$(COL_RED)Norminette KO !$(COL_RESET)'	\
	|| echo -e '$(COL_GREEN)Norminette OK !$(COL_RESET)'