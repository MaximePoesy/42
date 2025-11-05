#include <iostream>
#include <string>
#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	type = "WrongCat";
	std::cout << "WrongCat Constructor called for " << type << std::endl;
}


WrongCat::~WrongCat()
{
	std::cout << "WrongCat Destructor called for " << type << std::endl;
}

WrongCat::WrongCat(const WrongCat &other)
{
	*this = other;
	std::cout << "WrongCat Copy constructor called for " << type << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	std::cout << "WrongCat Assignment operator called for " << type << std::endl;
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << type << " says " << "Moew" << std::endl;
}
