/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:59:04 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/03 14:26:18 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0)
{
}

Point::Point(float a, float b) : x(a), y(b)
{
}

Point::~Point()
{
}

// Copy constructor
Point::Point(const Point &other) : x(other.x), y(other.y)
{
}

// Assignment operator
Point &Point::operator=(const Point &other)
{
	static_cast<void>(other);
	return (*this); // Assignment is not valid with const members
}

// Getter
Fixed Point::GetxValue() const
{
	return (x);
}

Fixed Point::GetyValue() const
{
	return (y);
}

Point Point::operator-(const Point &other) const
{
	return (Point((x - other.x).toFloat(), (y - other.y).toFloat()));
}
