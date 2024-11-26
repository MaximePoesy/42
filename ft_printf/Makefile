NAME = libftprintf.a

SRC = ft_printf/ft_printf.c \
      ft_printf/formatting/add_prefix.c \
      ft_printf/formatting/apply_flags.c \
      ft_printf/formatting/apply_width_and_padding.c \
      ft_printf/formatting/handle_zero.c \
      ft_printf/helper/ft_itoa_base.c \
      ft_printf/helper/ft_utoa.c \
      ft_printf/parsing/parse_flags.c \
      ft_printf/parsing/parse_format.c \
      ft_printf/parsing/parse_precision.c \
      ft_printf/parsing/parse_width.c \
      ft_printf/print/print_c.c \
      ft_printf/print/print_cx.c \
      ft_printf/print/print_d.c \
      ft_printf/print/print_p.c \
      ft_printf/print/print_prc.c \
      ft_printf/print/print_s.c \
      ft_printf/print/print_u.c \
      ft_printf/print/print_x.c

BONUS_SRC = ft_printf_bonus/ft_printf_bonus.c \
	    ft_printf_bonus/formatting/add_prefix_bonus.c \
	    ft_printf_bonus/formatting/apply_flags_bonus.c \
	    ft_printf_bonus/formatting/apply_width_and_padding_bonus.c \
	    ft_printf_bonus/formatting/handle_zero_bonus.c \
	    ft_printf_bonus/helper/ft_itoa_base_bonus.c \
	    ft_printf_bonus/helper/ft_utoa_bonus.c \
	    ft_printf_bonus/parsing/parse_flags_bonus.c \
	    ft_printf_bonus/parsing/parse_format_bonus.c \
	    ft_printf_bonus/parsing/parse_precision_bonus.c \
	    ft_printf_bonus/parsing/parse_width_bonus.c \
	    ft_printf_bonus/print/print_c_bonus.c \
	    ft_printf_bonus/print/print_cx_bonus.c \
	    ft_printf_bonus/print/print_d_bonus.c \
	    ft_printf_bonus/print/print_p_bonus.c \
	    ft_printf_bonus/print/print_prc_bonus.c \
	    ft_printf_bonus/print/print_s_bonus.c \
	    ft_printf_bonus/print/print_u_bonus.c \
	    ft_printf_bonus/print/print_x_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFLAGS = -L $(LIBFT_DIR) -lft
LIBFT_OBJ = $(LIBFT_DIR)/*.o

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)	
	ar rcs $@ $(OBJ) $(LIBFT_OBJ)
	ranlib $@

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(OBJ) $(BONUS_OBJ) $(LIBFT)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ) $(LIBFT_OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
