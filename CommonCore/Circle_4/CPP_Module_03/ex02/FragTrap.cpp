/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:52:03 by mpoesy            #+#    #+#             */
/*   Updated: 2025/11/04 16:52:05 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	health = 100;
	energy = 100;
	attackDamage = 30;
	std::cout << "FragTrap Default constructor called for " << name << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	health = 100;
	energy = 100;
	attackDamage = 30;
	std::cout << "FragTrap Name constructor called for " << name << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor called for " << name << std::endl;
}

FragTrap::FragTrap(const FragTrap &other)
{
	*this = other;
	std::cout << "FragTrap Copy constructor called for " << name << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	if (this != &other)
	{
		this->name = other.getName();
		this->health = other.getHealth();
		this->energy = other.getEnergy();
		this->attackDamage = other.getAttack();
	}
	std::cout << "Assignment operator called for " << name << std::endl;
	return (*this);
}

void FragTrap::attack(const std::string &target)
{
	if (this->health == 0 || this->energy == 0)
	{
		if (this->health == 0)
		{
			std::cout << "FragTrap " << name << " is dead and can't attack!"
			 	  << std::endl;
		}
		else
		{
			std::cout << "FragTrap " << name << " has no energy and can't attack!"
			 	  << std::endl;
		}
	}
	else
	{
		std::cout << "FragTrap " << name << " attacks " << target
		          << ", causing " << attackDamage << " points of damage!" << std::endl;
		energy--;
	}
}

void FragTrap::highFivesGuys()
{
	if (this->energy != 0)
	{
		std::cout << name << " High Fives!" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << name << " has no energy and can't high five!"
			 	 << std::endl;
	}
}
