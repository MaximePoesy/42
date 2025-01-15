CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -lm -lX11 -lXext
SRC = fract_ol.c
OBJ = $(SRC:.c=.o)
NAME = fractol

MLX_DIR = minilibx-linux
LIBFT_DIR = libft

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	cd $(MLX_DIR) && make && cd ..
	cd $(LIBFT_DIR) && make && cd ..

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	cd $(MLX_DIR) && make clean && cd ..
	cd $(LIBFT_DIR) && make clean && cd ..

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && make fclean && cd ..

re: clean all
