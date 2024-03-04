# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amassias <amassias@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 17:28:24 by amassias          #+#    #+#              #
#    Updated: 2024/03/04 17:52:23 by amassias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	cc
NAME			:=	philo
THIRD_PARTY_DIR	:=	third-party
SRC_DIR			:=	sources
INC_DIR			:=	includes
BIN_DIR			:=	binaries

# **************************************************************************** #
#                                                                              #
# Third party libraries                                                        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
# Compiler flags                                                               #
#                                                                              #
# **************************************************************************** #

CFLAGS			:=					\
	-I$(INC_DIR)					\
	-Wall -Werror -Wextra			\

LFLAGS			:=					\
	-lpthread						\

# **************************************************************************** #
#                                                                              #
# Files                                                                        #
#                                                                              #
# **************************************************************************** #

FILES			:=															\
	utils/chars																\
	utils/readers															\
	logging																	\
	main																	\
	running_helpers															\

SRCS			:=	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(FILES)))

OBJS			:=	$(addprefix $(BIN_DIR)/,$(addsuffix .o,$(FILES)))

# **************************************************************************** #
#                                                                              #
# Phony rules                                                                  #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re cleanlibs fcleanlibs norminette debug run

all: $(NAME)

bonus: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

cleanlibs:

fcleanlibs:

re:	fclean all

norminette:
	@norminette												\
		`find $(SRC_DIR) -type f -name \*.c`				\
		`find $(INC_DIR) -type f -name \*.h`				\
		| grep -Ev '^Notice: |OK\!$$'						\
		&& exit 1 || printf 'Norminette OK!\n' && exit 0

debug: $(NAME)
	@valgrind							\
	--show-leak-kinds=all				\
	--leak-check=full					\
	./$(NAME)

run: $(NAME)
	@./$(NAME)

# **************************************************************************** #
#                                                                              #
# Binary rules                                                                 #
#                                                                              #
# **************************************************************************** #

$(NAME): $(LIB_FT) $(LIB_MLX) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)