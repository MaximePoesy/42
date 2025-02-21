NAME_1 = server
NAME_2 = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME_1) $(NAME_2)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME_1): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_1)

$(NAME_2): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_2)

clean:
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME_1) $(NAME_2)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
