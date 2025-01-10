CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -lm -lX11 -lXext
SRC = fract_ol.c
OBJ = $(SRC:.c=.o)
NAME = fract_ol

MLX_DIR = minilibx-linux

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	cd $(MLX_DIR) && make

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	cd $(MLX_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(MLX_DIR) && make fclean

re: clean all
