# Define color codes
RESET = \\033[0m
GREEN = \\033[32m
BLUE = \\033[34m
YELLOW = \\033[33m

NAME = Philosophers

SRC =  loop.c \
       philo/eating.c \
       sentinel_loop.c \
       utils/ft_atoi.c \
       utils/init.c \
       utils/timestamp.c \
       main.c \
       utils/cleanup.c \
       utils/has_died.c \
       utils/print_action.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "$(BLUE)Compiling Philosophers objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Philosphers compiled!$(RESET)"

all: $(NAME)

clean:
	@echo "$(BLUE)Cleaning Philosophers object files ...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)Philosophers CLEANED!$(RESET)"

fclean: clean
	@echo "$(BLUE)Cleaning Philosophers executable files ...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Philosophers FCLEANED!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
