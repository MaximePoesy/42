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

all: $(NAME) $(FT_PRINTF)

$(NAME): echo_compiling $(OBJ) $(FT_PRINTF)
	@echo "Archiving libft files..."
	@cp $(FT_PRINTF) $(NAME)
	@ar rcs $(NAME) $(OBJ)
	@echo "DONE !"

echo_compiling:
	@echo "Compiling source files..."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)
	
clean:
	@echo "Removing libft files..."
	@rm -f $(OBJ)
	@make -s -C $(FT_PRINTF_DIR) clean
	@echo "CLEANED !"

fclean: clean
	@echo "Removing executables..."
	@rm -f $(NAME)
	@make -s -C $(FT_PRINTF_DIR) fclean
	@echo "exec CLEANED !"

re: fclean all

.PHONY:	all clean fclean re bonus
