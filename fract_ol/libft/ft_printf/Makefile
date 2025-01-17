NAME = libftprintf.a

SRC = ft_printf/ft_printf.c \
      ft_printf/formatting/add_prefix.c \
      ft_printf/formatting/apply_flags.c \
      ft_printf/formatting/apply_hash_flag.c \
      ft_printf/formatting/apply_width_and_padding.c \
      ft_printf/formatting/apply_width_and_padding_two.c \
      ft_printf/formatting/handle_zero.c \
      ft_printf/formatting/precision/precision_d.c \
      ft_printf/formatting/precision/precision_u.c \
      ft_printf/formatting/precision/precision_s.c \
      ft_printf/formatting/precision/precision_x.c \
      ft_printf/formatting/precision/precision_cx.c \
      ft_printf/helper/ft_itoa_base.c \
      ft_printf/helper/ft_utoa.c \
      ft_printf/helper/null_problem.c \
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
	    ft_printf_bonus/formatting/apply_hash_flag_bonus.c \
	    ft_printf_bonus/formatting/apply_width_and_padding_bonus.c \
	    ft_printf_bonus/formatting/apply_width_and_padding_two_bonus.c \
	    ft_printf_bonus/formatting/handle_zero_bonus.c \
	    ft_printf_bonus/formatting/precision/precision_d_bonus.c \
            ft_printf_bonus/formatting/precision/precision_u_bonus.c \
            ft_printf_bonus/formatting/precision/precision_s_bonus.c \
            ft_printf_bonus/formatting/precision/precision_x_bonus.c \
            ft_printf_bonus/formatting/precision/precision_cx_bonus.c \
	    ft_printf_bonus/helper/ft_itoa_base_bonus.c \
	    ft_printf_bonus/helper/ft_utoa_bonus.c \
	    ft_printf_bonus/helper/null_problem_bonus.c \
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

all: $(NAME)

$(NAME): echo_compiling $(OBJ) 
	@echo "Archiving ft_printf..."
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "ft_printf BUILT!"

bonus: echo_compiling $(OBJ) $(BONUS_OBJ)
	@echo "Archiving ft_printf..."
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@ranlib $(NAME)
	@echo "ft_printf_bonus BUILT!"

echo_compiling:
	@echo "Compiling source files..."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning ft_printf files..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo "ft_printf & ft_printf_bonus CLEANED!"

fclean:
	@echo "Cleaning ft_printf files..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo "Cleaning ft_printf executables..."
	@rm -f $(NAME)
	@echo "ft_printf & ft_printf_bonus FCLEANED!"

re: fclean all

.PHONY: all clean fclean re bonus
