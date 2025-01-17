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
	@echo "Cleaning fractol object files..."
	@rm -f $(OBJ)
	@echo "Cleaning MiniLibX object files..."
	@make -s -C $(MLX_DIR) clean
	@echo "Cleaning libft object files..."
	@make -s -C $(LIBFT_DIR) clean
	@echo "fract_ol CLEANED!"

fclean:
	@echo "Cleaning fractol object files..."
	@rm -f $(OBJ)
	@echo "Removing libft archive..."
	@make -s -C $(LIBFT_DIR) fclean
	@echo "Removing fractol executable..."
	@rm -f $(NAME)
	@echo "fract_ol FCLEANED!"

re: clean all
