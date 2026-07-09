/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:12:24 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 13:28:35 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PhoneBook.hpp"
#include <string>
#include <sstream>

PhoneBook::PhoneBook()
{
	index = 0;
	count = 0;
}

void	PhoneBook::addContact(Contact& contact)
{
	con[index % 8] = contact;
        index = (index + 1) % 8;
	if (count < 8)
		count++;
}

std::string	formatField(const std::string& str)
{
    if (str.length() > 10)
        return (str.substr(0, 9) + ".");
    else
        return (std::string(10 - str.length(), ' ') + str);
}

void	PhoneBook::showContactTable()
{
	std::cout << formatField("Index") << "|"
		  << formatField("First Name") << "|"
		  << formatField("Last Name") << "|"
		  << formatField("Nickname") << std::endl;

    for (int i = 0; i < count; ++i)
    {
        std::string fname = con[i].getFirstName();
        std::string lname = con[i].getLastName();
        std::string nick = con[i].getNickname();

	std::stringstream ss;
	ss << i;
	std::string i_str = ss.str();

        std::cout << formatField(i_str) << "|"
                  << formatField(fname) << "|"
                  << formatField(lname) << "|"
                  << formatField(nick) << std::endl;
    }
}

void	PhoneBook::showContact(int index)
{
	if (index < 0 || index >= count)
	{
		std::cout << "Index must be between 0 and the highest contact number." << std::endl;
		return ;
	}

	std::cout << "First name : " << con[index].getFirstName() << std::endl;
	std::cout << "Last name : " << con[index].getLastName() << std::endl;
	std::cout << "Nickname : " << con[index].getNickname() << std::endl;
	std::cout << "Phone number : " << con[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest secret : " << con[index].getDarkestSecret() << std::endl;
}
