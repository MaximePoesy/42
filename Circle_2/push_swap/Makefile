# Define color codes
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m


CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft
LDFLAGS = -Llibft -lft
SRC = 	push_swap.c \
	parsing.c \
	operations/operations_a.c \
	operations/operations_b.c \
	operations/operations_c.c \
	sort/sort.c \
	sort/sort_two.c \
	isnt_sorted.c

OBJ = $(SRC:.c=.o)
NAME = push_swap

LIBFT_DIR = libft

all: $(NAME)

$(LIBFT_DIR)/libft.a:
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@cd $(LIBFT_DIR) && make -s && cd ..
	@echo "$(GREEN)libft COMPILED!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@echo "$(BLUE)Linking the project...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Project LINKED!$(RESET)"

clean:
	@echo "$(BLUE)Cleaning push_swap object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(BLUE)Cleaning libft object files...$(RESET)"
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(GREEN)push_swap CLEANED!$(RESET)"

fclean:
	@echo "$(BLUE)Cleaning fractol object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(BLUE)Removing libft archive...$(RESET)"
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Removing push_swap executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)push_swap FCLEANED!$(RESET)"

re: fclean all

.phony : clean fclean re
