#include <iostream>
#include <string>
#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog()
{
	type = "Dog";
	brain = new Brain();
	std::cout << "Dog Constructor called for " << type << std::endl;
}


Dog::~Dog()
{
	delete brain;
	std::cout << "Dog Destructor called for " << type << std::endl;
}

Dog::Dog(const Dog &other)
{
	this->type = other.type;
	brain = new Brain(*other.brain);
	std::cout << "Dog Copy constructor called for " << type << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		this->type = other.type;
		delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Dog Assignment operator called for " << type << std::endl;
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << type << " says " << "Woof" << std::endl;
}
