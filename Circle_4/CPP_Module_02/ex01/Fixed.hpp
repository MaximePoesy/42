/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:52:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/30 11:13:31 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
	private:
		int			fullValue;
		static const int	nbFractionalBits;
	public:
		Fixed();
		Fixed(const int value);
		Fixed(const float value);
		~Fixed();
		Fixed(const Fixed& other);
		Fixed&			operator=(const Fixed& other);
		int			getRawBits( void ) const;
		void			setRawBits( int const raw);
		float			toFloat( void ) const;
		int			toInt( void ) const;
};

std::ostream&	operator<<(std::ostream& os, const Fixed& fixed);

#endif
