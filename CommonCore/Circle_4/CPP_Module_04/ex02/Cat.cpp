#include <iostream>
#include <string>
#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat()
{
	type = "Cat";
	brain = new Brain();
	std::cout << "Cat Constructor called for " << type << std::endl;
}


Cat::~Cat()
{
	delete brain;
	std::cout << "Cat Destructor called for " << type << std::endl;
}

Cat::Cat(const Cat &other)
{
	type = other.type;
	brain = new Brain(*other.brain);
	std::cout << "Cat Copy constructor called for " << type << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		this->type = other.type;
		delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Cat Assignment operator called for " << type << std::endl;
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << type << " says " << "Moew" << std::endl;
}
