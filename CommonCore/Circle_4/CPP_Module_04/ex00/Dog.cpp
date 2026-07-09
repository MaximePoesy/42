#include <iostream>
#include <string>
#include "Dog.hpp"

Dog::Dog()
{
	type = "Dog";
	std::cout << "Dog Constructor called for " << type << std::endl;
}


Dog::~Dog()
{
	std::cout << "Dog Destructor called for " << type << std::endl;
}

Dog::Dog(const Dog &other)
{
	*this = other;
	std::cout << "Dog Copy constructor called for " << type << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout << "Dog Assignment operator called for " << type << std::endl;
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << type << " says " << "Woof" << std::endl;
}
