# Define color codes
RESET = \033[0m
GREEN = \033[32m
BLUE = \033[34m
YELLOW = \033[33m

NAME_1 = server
NAME_2 = client

SRCS_SERVER = server.c server_util.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(LIBFT) $(NAME_1) $(NAME_2)

$(LIBFT):
	@echo "$(BLUE)Compiling libft ...$(RESET)"
	@make -s -C $(LIBFT_DIR)

$(NAME_1): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_1)

$(NAME_2): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_2)

clean:
	@echo "$(BLUE)Cleaning Minitalk object files ...$(RESET)"
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	@make -s clean -C $(LIBFT_DIR)
	@echo "$(GREEN)Minitalk CLEANED!$(RESET)"

fclean: clean
	@echo "$(BLUE)Cleaning Minitalk executable files ...$(RESET)"
	@rm -f $(NAME_1) $(NAME_2)
	@make -s fclean -C $(LIBFT_DIR)
	@echo "$(GREEN)Minitalk FCLEANED!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
