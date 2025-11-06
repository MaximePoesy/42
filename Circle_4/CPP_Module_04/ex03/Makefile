NAME = Interface
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp AMateria.cpp Character.cpp Cure.cpp Ice.cpp MateriaSource.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
