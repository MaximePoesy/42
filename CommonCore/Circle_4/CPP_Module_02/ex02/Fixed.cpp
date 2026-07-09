/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:19:20 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/02 14:00:58 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

const int Fixed::nbFractionalBits = 8;

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
	float	temp;

	std::cout << "Float constructor called" << std::endl;
	temp = value;
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
Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

// Copy assignment operator
Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		fullValue = other.getRawBits();
	}
	return (*this);
}

// Getter
int Fixed::getRawBits() const
{
	return (fullValue);
}

// Setter
void Fixed::setRawBits(int const raw)
{
	fullValue = raw;
}

float Fixed::toFloat(void) const
{
	float temp = fullValue;
	for (int i = 0; i < nbFractionalBits; i++)
	{
		temp /= 2;
	}
	return (temp);
}

int Fixed::toInt(void) const
{
	return (fullValue >> nbFractionalBits);
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}

// Comparison operators
bool Fixed::operator>(const Fixed &other) const
{
	return (fullValue > other.fullValue);
}

bool Fixed::operator<(const Fixed &other) const
{
	return (fullValue < other.fullValue);
}

bool Fixed::operator>=(const Fixed &other) const
{
	return (fullValue >= other.fullValue);
}

bool Fixed::operator<=(const Fixed &other) const
{
	return (fullValue <= other.fullValue);
}

bool Fixed::operator==(const Fixed &other) const
{
	return (fullValue == other.fullValue);
}

bool Fixed::operator!=(const Fixed &other) const
{
	return (fullValue != other.fullValue);
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &other) const
{
	return (Fixed(this->toFloat() + other.toFloat()));
}

Fixed Fixed::operator-(const Fixed &other) const
{
	return (Fixed(this->toFloat() - other.toFloat()));
}

Fixed Fixed::operator*(const Fixed &other) const
{
	return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed Fixed::operator/(const Fixed &other) const
{
	return (Fixed(this->toFloat() / other.toFloat()));
}

// Increment / Decrement operators

// Prefix : ++a
Fixed &Fixed::operator++()
{
	++fullValue;
	return (*this);
}

// Postfix : a++
Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	++(*this);
	return (temp);
}

// Prefix --a
Fixed &Fixed::operator--()
{
	--fullValue;
	return (*this);
}

// Postfix : a--
Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	--(*this);
	return (temp);
}

// Min (non-const)
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return ((a < b) ? a : b);
}

// Min (const)
const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return ((a < b) ? a : b);
}

// Max (non-const)
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return ((a > b) ? a : b);
}

// Max (const)
const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return ((a > b) ? a : b);
}
