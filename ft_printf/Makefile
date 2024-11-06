NAME = ft_printf

SRC = main.c ft_printf.c
BONUS_SRC = _bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_MAKE = $(LIBFT_DIR)/Makefile

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/$(NAME)
		$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFT_DIR) -lft

$(LIBFT_DIR)/$(NAME):
		$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)
		$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
		rm -f $(NAME)
		$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(BONUS_OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft

bonus_clean:
		rm -f $(BONUS_OBJ)

.PHONY: all clean fclean re bonus bonus_clean
