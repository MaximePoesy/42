/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:01:05 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/03 17:20:18 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

ClapTrap::ClapTrap()
{
	health = 10;
	energy = 10;
	attack = 0;
	name = "Bumblebee";
}

ClapTrap::ClapTrap(std::string name)
{
	health = 10;
	energy = 10;
	attack = 0;
	this->name = name;
}

ClapTrap::~ClapTrap()
{
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	if (this != &other)
	{
		this->name = other.getName();
		this->health = other.getHealth();
		this->energy = other.getEnergy();
		this->attack = other.getATtack();
	}
	return (*this);
}

ClapTrap::operator=(const ClapTrap &other)
{
	return (this->name = other.getName() &&
			this->health = other.getHealth() &&
			this->energy = other.getEnergy() &&
			this->attack = other.getATtack())
}

void	ClapTrap::attack(const std::string& target)
{
	std::cout << "ClapTrap " << this->name << 
	" attacks " << target <<
	", causing " << this->attack <<
       	" points of damage!" << std::endl;
}

void 
