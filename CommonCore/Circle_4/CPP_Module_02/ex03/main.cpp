/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:19:28 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/03 15:05:32 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

float	dot(Point const a, Point const b)
{
	return ((a.GetxValue().toFloat() * b.GetyValue().toFloat())
		- (b.GetxValue().toFloat() * a.GetyValue().toFloat()));
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	float	d;
	float	e;
	float	f;

	d = dot(b - a, point - a);
	e = dot(c - b, point - b);
	f = dot(a - c, point - c);
	if (d > 0 && e > 0 && f > 0)
		return (true);
	if (d < 0 && e < 0 && f < 0)
		return (true);
	return (false);
}

void	runTest(Point const &a, Point const &b, Point const &c, Point const &p,
		int testNum)
{
	bool	result;

	result = bsp(a, b, c, p);
	std::cout << "Test " << testNum << ": Point (" << p.GetxValue() << "," << p.GetyValue() << ") is " << (result ? "INSIDE" : "OUTSIDE") << " the triangle. " << "[Expected: ";
	switch (testNum)
	{
	case 1:
		std::cout << "INSIDE";
		break ; // inside (1,1)
	case 2:
		std::cout << "OUTSIDE";
		break ; // on edge AB (2,0)
	case 3:
		std::cout << "OUTSIDE";
		break ; // on vertex A (0,0)
	case 4:
		std::cout << "OUTSIDE";
		break ; // outside (5,5)
	case 5:
		std::cout << "INSIDE";
		break ; // nearly inside (0.1,0.1)
	case 6:
		std::cout << "INSIDE";
		break ; // center-ish (1.5,1.5)
	default:
		std::cout << "UNKNOWN";
		break ;
	}
	std::cout << "]" << std::endl;
}

int	main(void)
{
	// Triangle: a simple right triangle
	Point a(0.0f, 0.0f);
	Point b(4.0f, 0.0f);
	Point c(0.0f, 4.0f);
	std::cout << "Triangle vertices:\n";
	std::cout << "A: (" << a.GetxValue() << ", " << a.GetyValue() << ")\n";
	std::cout << "B: (" << b.GetxValue() << ", " << b.GetyValue() << ")\n";
	std::cout << "C: (" << c.GetxValue() << ", " << c.GetyValue() << ")\n\n";
	// Test cases
	Point inside(1.0f, 1.0f);       // Inside
	Point edge(2.0f, 0.0f);         // On edge AB
	Point vertex(0.0f, 0.0f);       // On vertex A
	Point outside(5.0f, 5.0f);      // Outside
	Point nearlyInside(0.1f, 0.1f); // Near vertex A
	Point center(1.5f, 1.5f);       // Center-ish
	runTest(a, b, c, inside, 1);
	runTest(a, b, c, edge, 2);
	runTest(a, b, c, vertex, 3);
	runTest(a, b, c, outside, 4);
	runTest(a, b, c, nearlyInside, 5);
	runTest(a, b, c, center, 6);
	return (0);
}
