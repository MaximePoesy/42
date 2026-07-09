NAME = spider

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -I/usr/include/libxml2  -std=c++17 # -std=c++98
LDFLAGS = -lcurl -lxml2

SRC = spider.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
