/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:56:35 by mpoesy            #+#    #+#             */
/*   Updated: 2025/07/03 14:31:27 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
  private:
	Fixed const x;
	Fixed const y;

  public:
	Point();
	Point(float a, float b);
	~Point();
	Point(const Point &other);
	Point &operator=(const Point &other);
	Fixed GetxValue() const;
	Fixed GetyValue() const;
	Point operator-(const Point &other) const;
};

#endif
