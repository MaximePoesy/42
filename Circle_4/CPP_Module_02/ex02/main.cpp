/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:48:33 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/02 14:03:41 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    section("Construction and Output");

    Fixed a;                      // Default constructor
    Fixed b(10);                  // Int constructor
    Fixed c(3.14f);               // Float constructor
    Fixed d(b);                   // Copy constructor
    Fixed e; e = c;               // Assignment operator

    std::cout << "a (default)      = " << a << std::endl;
    std::cout << "b (int 10)       = " << b << std::endl;
    std::cout << "c (float 3.14f)  = " << c << std::endl;
    std::cout << "d (copy of b)    = " << d << std::endl;
    std::cout << "e (assigned c)   = " << e << std::endl;

    section("Conversion Functions");

    std::cout << "b.toInt()        = " << b.toInt() << std::endl;
    std::cout << "c.toFloat()      = " << c.toFloat() << std::endl;

    section("Comparison Operators");

    Fixed x(5.5f);
    Fixed y(2.25f);

    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "x > y            = " << (x > y) << std::endl;
    std::cout << "x < y            = " << (x < y) << std::endl;
    std::cout << "x >= y           = " << (x >= y) << std::endl;
    std::cout << "x <= y           = " << (x <= y) << std::endl;
    std::cout << "x == y           = " << (x == y) << std::endl;
    std::cout << "x != y           = " << (x != y) << std::endl;

    section("Arithmetic Operators");

    Fixed sum = x + y;
    Fixed diff = x - y;
    Fixed prod = x * y;
    Fixed quot = x / y;

    std::cout << "x + y            = " << sum << std::endl;
    std::cout << "x - y            = " << diff << std::endl;
    std::cout << "x * y            = " << prod << std::endl;
    std::cout << "x / y            = " << quot << std::endl;

    section("Increment and Decrement");

    Fixed inc(1.0f);
    std::cout << "Original         = " << inc << std::endl;

    std::cout << "Pre-increment    = " << ++inc << std::endl;
    std::cout << "Post-increment   = " << inc++ << std::endl;
    std::cout << "After post-inc   = " << inc << std::endl;

    std::cout << "Pre-decrement    = " << --inc << std::endl;
    std::cout << "Post-decrement   = " << inc-- << std::endl;
    std::cout << "After post-dec   = " << inc << std::endl;

    section("Min and Max (Non-const)");

    Fixed p(4.2f);
    Fixed q(9.7f);

    std::cout << "p = " << p << ", q = " << q << std::endl;
    std::cout << "min(p, q)        = " << Fixed::min(p, q) << std::endl;
    std::cout << "max(p, q)        = " << Fixed::max(p, q) << std::endl;

    section("Min and Max (Const)");

    const Fixed cp(7.3f);
    const Fixed cq(7.31f);

    std::cout << "cp = " << cp << ", cq = " << cq << std::endl;
    std::cout << "min(cp, cq)      = " << Fixed::min(cp, cq) << std::endl;
    std::cout << "max(cp, cq)      = " << Fixed::max(cp, cq) << std::endl;

    return 0;
}
