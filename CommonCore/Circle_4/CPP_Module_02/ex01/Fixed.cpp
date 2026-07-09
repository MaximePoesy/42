/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:19:20 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/30 11:56:45 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"
#include <cmath>

const int	Fixed::nbFractionalBits = 8;

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	fullValue = 0;
}

Fixed::Fixed(const int value)
{
	std::cout << "Int constructor called" << std::endl;
	fullValue = value << nbFractionalBits;
}

Fixed::Fixed(const float value)
{
	std::cout << "Float constructor called" << std::endl;
	float	temp = value;
	for (int i = 0; i < nbFractionalBits; i++)
	{
		temp *= 2;
	}
	fullValue = static_cast<int>(roundf(temp));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

// Copy assignment operator
Fixed&	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		fullValue = other.getRawBits();
	}
	return (*this);
}

// Getter
int	Fixed::getRawBits() const
{
	return (fullValue);
}

// Setter
void	Fixed::setRawBits(int const raw)
{
	fullValue = raw;
}

float	Fixed::toFloat( void ) const
{
	float   temp = fullValue;
        for (int i = 0; i < nbFractionalBits; i++)
        {
                temp /= 2;
        }
	return (temp);
}

int	Fixed::toInt( void ) const
{
	return (fullValue >> nbFractionalBits);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}
