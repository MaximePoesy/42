# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:20:00 by staverni          #+#    #+#              #
#    Updated: 2025/05/18 12:34:47 by staverni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

CC          =	cc
CFLAGS      =	-Wall -Wextra -Werror -MMD -MP
LDFLAGS     =	-L$(LIB_DIR) -lft -lreadline
DEV_CFLAGS  =	-g3 -fstack-protector-strong -Wvla -O1
DEV_LDFLAGS =	-fsanitize=address,undefined,leak
PROD_FLAGS  =	-O3
MAKEFLAGS  +=	--no-print-directory -j$(nproc) --output-sync=target
INCLUDE_FLAGS =	-I $(INCLUDE_DIR) -I $(LIB_DIR)/include

ifeq ($(BUILD),dev)
	CFLAGS  +=	$(DEV_CFLAGS)
	LDFLAGS +=	$(DEV_LDFLAGS)
else ifeq ($(BUILD),valgrind)
	CFLAGS  +=	$(DEV_CFLAGS)
else
	CFLAGS  +=	$(PROD_FLAGS)
endif

OBJ_DIR     =	obj
INCLUDE_DIR =	include
LIB_DIR     =	lib

RESET  =	\033[0m
GRAY   =	\033[90m
RED    =	\033[31m
GREEN  =	\033[32m
YELLOW =	\033[33m
BLUE   =	\033[34m

LIB =	$(LIB_DIR)/libft.a

vpath		%.c src src/environ src/utils \
			src/expansion src/lexing src/parsing src/validation \
			src/builtins src/execution \

SRC_FILES =	main main_logic prompt signals \
			environ_utils environ path \
			exp_double exp_single exp_unquoted exp_word expand expansion \
			lexer_quoting lexer token_list tokens lexer_metachars \
			binop_node exec_node free_tree parse_line pipe_node print redirect_node tree_utils \
			post pre valid_utils \
			buffer errors \
			cd echo env exit export pwd unset \
			execution exec_builtin exec_cmd exec_pipe exec_redir exec_heredoc exec_utils

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:=.o))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(INCLUDE_FLAGS) $(CFLAGS) $(LDFLAGS)
	@echo "$(GREEN)✅ Program built: $@$(RESET)"

$(OBJ_DIR)/%.o: %.c $(LIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@
	@echo "$(GRAY)🔨 Compiled: $<$(RESET)"

$(LIB):
	@$(MAKE) -C $(LIB_DIR) $(MAKEFLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🧹 Minishell object files cleaned.$(RESET)"

fclean:
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@$(RM) -rf $(OBJ_DIR) $(NAME)
	@echo "$(BLUE)🧹 Minishell object files cleaned.$(RESET)"
	@echo "$(BLUE)🧼 Minishell binary removed.$(RESET)"

re: fclean
	@$(MAKE) $(NAME)

.PHONY: all clean fclean re test
