/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:46 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/25 11:10:26 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	Zombie* z = newZombie("HeapZombie");
	z->announce();
	delete z;

	randomChump("StackZombie");
	return 0;
}
