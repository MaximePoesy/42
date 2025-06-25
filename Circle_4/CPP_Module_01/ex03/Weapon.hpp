/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/25 17:30:45 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class	Weapon
{
	private:
		std::string	type;
	public:
		std::string	getType();
		void		setType(std::string Type);
		Weapon(std::string type);
		Weapon();
};

#endif
