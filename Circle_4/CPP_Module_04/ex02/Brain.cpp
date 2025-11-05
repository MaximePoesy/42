#include <iostream>
#include <string>
#include "Brain.hpp"

#include <string>

Brain::Brain()
{
	std::cout << "Brain Constructor called" << std::endl;
}


Brain::~Brain()
{
	std::cout << "Brain Destructor called" << std::endl;
}

Brain::Brain(const Brain &other)
{
	*this = other;
	std::cout << "Brain Copy constructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
        		this->ideas[i] = other.ideas[i];
	}
	std::cout << "Brain Assignment operator called" << std::endl;
	return (*this);
}
