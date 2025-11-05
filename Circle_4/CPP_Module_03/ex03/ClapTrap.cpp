/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:01:05 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/10 12:43:54 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	health = 10;
	energy = 10;
	attackDamage = 0;
	name = "Bumblebee";
	std::cout << "ClapTrap Default constructor called for " << name << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
	health = 10;
	energy = 10;
	attackDamage = 0;
	this->name = name;
	std::cout << "ClapTrap Name constructor called for " << name << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor called for " << name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	*this = other;
	std::cout << "ClapTrap Copy constructor called for " << name << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
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

void ClapTrap::attack(const std::string &target)
{
	if (this->health == 0 || this->energy == 0)
	{
		if (this->health == 0)
		{
			std::cout << "ClapTrap " << name << " is dead and can't attack!"
			 	  << std::endl;
		}
		else
		{
			std::cout << "ClapTrap " << name << " has no energy and can't attack!"
			 	  << std::endl;
		}
	}
	else
	{
		std::cout << "ClapTrap " << name << " attacks " << target
		          << ", causing " << attackDamage << " points of damage!" << std::endl;
		energy--;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " takes " << amount << " damage!" << std::endl;
	if (amount >= health)
		health = 0;
	else
		health -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energy == 0 || health == 0)
	{
		if (this->health == 0)
		{
			std::cout << "ClapTrap " << name << " is dead and can't repair!"
			 	  << std::endl;
		}
		else
		{
			std::cout << "ClapTrap " << name << " has no energy and can't repair!"
			 	  << std::endl;
		}
	}
	else
	{
		std::cout << "ClapTrap " << name << " repairs itself for " << amount
			  << " health points!" << std::endl;
		health += amount;
		energy--;
	}
}

std::string ClapTrap::getName() const
{
	return (name);
}

int ClapTrap::getHealth() const
{
	return (health);
}

int ClapTrap::getEnergy() const
{
	return (energy);
}

int ClapTrap::getAttack() const
{
	return (attackDamage);
}
