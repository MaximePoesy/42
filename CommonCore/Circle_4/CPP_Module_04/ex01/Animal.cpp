#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal()
{
	type = "Animal";
	std::cout << "Animal Constructor called for " << type << std::endl;
}


Animal::~Animal()
{
	std::cout << "Animal Destructor called for " << type << std::endl;
}

Animal::Animal(const Animal &other)
{
	*this = other;
	std::cout << "Animal Copy constructor called for " << type << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout << "Animal Assignment operator called for " << type << std::endl;
	return (*this);
}

void Animal::makeSound() const
{
	std::cout << type << " says " << "Wut?" << std::endl;
}

std::string Animal::getType() const
{
	return "type is : " + type;
}
