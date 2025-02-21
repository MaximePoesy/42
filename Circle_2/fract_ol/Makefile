# Define color codes
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m


CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Iminilibx-linux -Ilibft
LDFLAGS = -Lminilibx-linux -lmlx -lm -lX11 -lXext -Llibft -lft
SRC = 	fract_ol.c \
	color/color_shift.c \
	color/create_color.c \
	color/precompute.c \
	hook/key_hook.c \
	hook/mouse_hook.c \
	libx_utils/free.c \
	libx_utils/init.c \
	other/abs.c \
	other/check_set.c \
	other/data_setup.c \
	other/menu.c \
	pixel/burning_ship.c \
	pixel/display.c \
	pixel/julia.c \
	pixel/mandelbrot.c \
	pixel/zoom.c
OBJ = $(SRC:.c=.o)
NAME = fractol

MLX_DIR = minilibx-linux
LIBFT_DIR = libft

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)Compiling MinilibX...$(RESET)"
	@cd $(MLX_DIR) && make -s && cd ..
	@echo "$(GREEN)MinilibX COMPILED!$(RESET)"

$(LIBFT_DIR)/libft.a:
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@cd $(LIBFT_DIR) && make -s && cd ..
	@echo "$(GREEN)libft COMPILED!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	@echo "$(BLUE)Linking the project...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Project LINKED!$(RESET)"

clean:
	@echo "$(BLUE)Cleaning fractol object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)fractol object files CLEANED!$(RESET)"
	@echo "$(BLUE)Cleaning MiniLibX object files...$(RESET)"
	@make -s -C $(MLX_DIR) clean
	@echo "$(GREEN)MinilibX object files CLEANED!$(RESET)"
	@echo "$(BLUE)Cleaning libft object files...$(RESET)"
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(GREEN)libft object files CLEANED!$(RESET)"
	@echo "$(GREEN)fract_ol CLEANED!$(RESET)"

fclean:
	@echo "$(BLUE)Cleaning fractol object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)fractol object files CLEANED!$(RESET)"
	@echo "$(BLUE)Cleaning MiniLibX object files...$(RESET)"
	@make -s -C $(MLX_DIR) clean
	@echo "$(GREEN)MinilibX object files CLEANED!$(RESET)"
	@echo "$(BLUE)Removing libft archive...$(RESET)"
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)libft archive REMOVED!$(RESET)"
	@echo "$(BLUE)Removing fractol executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)fractol exectuable REMOVED!$(RESET)"
	@echo "$(GREEN)fract_ol FCLEANED!$(RESET)"

re: fclean all

.phony : clean fclean re
