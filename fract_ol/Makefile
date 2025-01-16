CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Iminilibx-linux -Ilibft
LDFLAGS = -Lminilibx-linux -lmlx -lm -lX11 -lXext -Llibft -lft
SRC = fract_ol.c
OBJ = $(SRC:.c=.o)
NAME = fractol

MLX_DIR = minilibx-linux
LIBFT_DIR = libft

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@echo "Compiling minilibx..."
	@cd $(MLX_DIR) && make -s && cd ..
	@echo "Compiling libft..."
	@cd $(LIBFT_DIR) && make -s && cd ..

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	@echo "Linking the project..."
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "Removing object files from minilibx..."
	@cd $(MLX_DIR) && make clean && cd ..
	@echo "Removing object files from libft..."
	@cd $(LIBFT_DIR) && make clean && cd ..

fclean: clean
	@echo "Removing object files from libft..."
	@cd $(LIBFT_DIR) && make fclean && cd ..
	@echo "Cleaning executable files..."
	@rm -f $(NAME)

re: clean all
