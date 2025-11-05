/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:55:06 by mpoesy            #+#    #+#             */
/*   Updated: 2025/11/05 10:55:07 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ClapTrap.hpp"
//#include "ScavTrap.hpp"
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("Bumblebee_clap_name")
{
	this->health = 100;
	this->energy = 50;
	this->attackDamage = 30;
	this->name = "Bumblebee";
	std::cout << "DiamondTrap Default constructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name")
{
	this->health = 100;
	this->energy = 50;
	this->attackDamage = 30;
	this->name = name;
	std::cout << "DiamondTrap Name constructor called for " << name << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap Destructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
{
	*this = other;
	std::cout << "DiamondTrap Copy constructor called for " << name << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
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

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap's name : " << name << std::endl
		  << "ClapTrap's name : " << ClapTrap::name << std::endl;
}
