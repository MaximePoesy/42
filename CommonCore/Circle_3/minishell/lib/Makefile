# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 12:22:00 by staverni          #+#    #+#              #
#    Updated: 2025/05/17 15:28:00 by staverni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC            =	cc
CFLAGS        =	-Wall -Wextra -Werror -MMD -MP
DEV_CFLAGS    =	-g3 -fstack-protector-strong -Wvla -O1
PROD_FLAGS    =	-O3 -fstack-protector-strong
MAKEFLAGS    +=	--no-print-directory -j$(nproc) --output-sync=target
INCLUDE_FLAGS =	-I $(INCLUDE)

ifeq ($(BUILD),dev)
	CFLAGS  +=	$(DEV_CFLAGS)
else
	CFLAGS  +=	$(PROD_FLAGS)
endif

OBJ_DIR =	obj
INCLUDE =	include

RESET  =	\033[0m
GRAY   =	\033[90m
GREEN  =	\033[32m
BLUE   =	\033[34m

vpath %.c src src/printf

SRC_FILES = \
	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_iswhitespace ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
	ft_strlcpy ft_strlcat ft_strcspn ft_toupper ft_tolower ft_strchr \
	ft_strtok ft_strrchr ft_strcmp ft_strncmp ft_memchr ft_memcmp ft_strnstr \
	ft_atoi ft_calloc ft_strdup ft_strndup ft_substr ft_strjoin ft_strpbrk \
	ft_strtrim ft_strspn ft_split ft_itoa ft_realloc ft_strmapi ft_striteri \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstfind \
	ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter \
	ft_lstmap ft_lstpop ft_swap ft_strswap \
	case_c case_di case_p case_s case_u case_x ft_printf

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:=.o))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) rcs $@ $(OBJ)
	@echo "$(GREEN)✅ Archive built: $@$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@
	@echo "$(GRAY)🔨 Compiled: $<$(RESET)"

-include $(DEP)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(BLUE)🧹 Libft object files cleaned.$(RESET)"

fclean: clean
	@$(RM) -rf $(NAME)
	@echo "$(BLUE)🧼 Libft library removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
