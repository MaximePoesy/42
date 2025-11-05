#include <iostream>
#include <string>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	type = "WrongAnimal";
	std::cout << "WrongAnimal Constructor called for " << type << std::endl;
}


WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal Destructor called for " << type << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other)
{
	*this = other;
	std::cout << "WrongAnimal Copy constructor called for " << type << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout << "WrongAnimal Assignment operator called for " << type << std::endl;
	return (*this);
}

void WrongAnimal::makeSound() const
{
	std::cout << type << " says " << "Wut?" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return "type is : " + type;
}
