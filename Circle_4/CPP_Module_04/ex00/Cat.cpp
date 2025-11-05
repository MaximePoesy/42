#include <iostream>
#include <string>
#include "Cat.hpp"

Cat::Cat()
{
	type = "Cat";
	std::cout << "Cat Constructor called for " << type << std::endl;
}


Cat::~Cat()
{
	std::cout << "Cat Destructor called for " << type << std::endl;
}

Cat::Cat(const Cat &other)
{
	*this = other;
	std::cout << "Cat Copy constructor called for " << type << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout << "Cat Assignment operator called for " << type << std::endl;
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << type << " says " << "Moew" << std::endl;
}
