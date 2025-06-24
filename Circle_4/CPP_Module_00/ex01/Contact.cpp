/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:24:14 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 13:05:35 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <string>

void	Contact::setContact(std::string& first_name, std::string& last_name, std::string& nickname, unsigned long long& phone_number, std::string& darkest_secret)
{
	this->first_name = first_name.empty() ? " " : first_name;
	this->last_name = last_name.empty() ? " " : last_name;
	this->nickname = nickname.empty() ? " " : nickname;
	if (phone_number > 9999999999)
		this->phone_number = 9999999999;
	else
		this->phone_number = phone_number;
	this->darkest_secret = darkest_secret.empty() ? " " : darkest_secret;
}

std::string	Contact::getFirstName()
{
	return (first_name);
}

std::string	Contact::getLastName()
{
	return (last_name);
}

std::string	Contact::getNickname()
{
	return (nickname);
}

unsigned long long	Contact::getPhoneNumber()
{
        return (phone_number);
}

std::string	Contact::getDarkestSecret()
{
        return (darkest_secret);
}
