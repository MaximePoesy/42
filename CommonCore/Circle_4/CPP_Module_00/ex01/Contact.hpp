/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:22:39 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 13:34:16 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
private:
    std::string	first_name;
    std::string	last_name;
    std::string	nickname;
    unsigned long long	phone_number;
    std::string	darkest_secret;

public:
    void	setContact(std::string& first_name, std::string& last_name, std::string& nickname, unsigned long long& phone_number, std::string& darkest_secret);
    std::string	getFirstName();
    std::string	getLastName();
    std::string	getNickname();
    unsigned long long	getPhoneNumber();
    std::string getDarkestSecret();
};

#endif
