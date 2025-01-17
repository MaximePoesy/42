SRC = ft_strlen.c ft_memset.c ft_bzero.c ft_isalpha.c ft_isdigit.c \
      ft_isalnum.c ft_isascii.c ft_isprint.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      ft_strcmp.c ft_isspace.c ft_atof.c ft_ftoa.c ft_is_float.c

NAME = libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Default target
all: $(NAME)

# Building the library
$(NAME): $(OBJ) $(FT_PRINTF)
	@echo "Archiving libft files..."
	@ar rcs $(NAME) $(OBJ)
	@echo "Adding ft_printf..."
	@cp $(FT_PRINTF) $(NAME)
	@echo "libft BUILT!"

# Building ft_printf
$(FT_PRINTF):
	@echo "Compiling ft_printf..."
	@make -s -C $(FT_PRINTF_DIR)

# Object file compilation
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning object files
clean:
	@echo "Cleaning libft object files..."
	@rm -f $(OBJ)
	@echo "Cleaning ft_printf..."
	@make -s -C $(FT_PRINTF_DIR) clean
	@echo "libft CLEANED!"

# Full cleanup
fclean:
	@echo "Cleaning libft object files..."
	@rm -f $(OBJ)
	@echo "Removing libft archive..."
	@rm -f $(NAME)
	@echo "Cleaning ft_printf archive..."
	@make -s -C $(FT_PRINTF_DIR) fclean
	@echo "libft FCLEANED!"

re: fclean all

.PHONY:	all clean fclean re bonus
