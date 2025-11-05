/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:55:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/11/04 11:55:37 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	health = 100;
	energy = 50;
	attackDamage = 20;
	std::cout << "ScavTrap Default constructor called for " << name << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	health = 100;
	energy = 50;
	attackDamage = 20;
	std::cout << "ScavTrap Name constructor called for " << name << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor called for " << name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other)
{
	*this = other;
	std::cout << "ScavTrap Copy constructor called for " << name << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
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

void ScavTrap::attack(const std::string &target)
{
	if (this->health == 0 || this->energy == 0)
	{
		if (this->health == 0)
		{
			std::cout << "ScavTrap " << name << " is dead and can't attack!"
			 	  << std::endl;
		}
		else
		{
			std::cout << "ScavTrap " << name << " has no energy and can't attack!"
			 	  << std::endl;
		}
	}
	else
	{
		std::cout << "ScavTrap " << name << " attacks " << target
		          << ", causing " << attackDamage << " points of damage!" << std::endl;
		energy--;
	}
}

void ScavTrap::guardGate()
{
	std::cout << name << " is now in Gatekeeper mode." << std::endl;
}
