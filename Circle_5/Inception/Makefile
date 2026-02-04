NAME = inception
COMPOSE = srcs/docker-compose.yml
DATA = /home/mpoesy/data

all:
	@mkdir -p $(DATA)/mariadb $(DATA)/wordpress
	@docker-compose -f $(COMPOSE) up -d --build

down:
	@docker-compose -f $(COMPOSE) down

clean:
	@docker-compose -f $(COMPOSE) down -v
	@docker system prune -af

fclean: clean
	@sudo rm -rf $(DATA)/mariadb/* $(DATA)/wordpress/*

re: fclean all

.PHONY: all down clean fclean re
