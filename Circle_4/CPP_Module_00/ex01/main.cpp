/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:03:20 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 15:48:58 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iostream>
#include <string>
#include <sstream>

std::string sanitizeInput(const std::string& input) {
    std::string sanitized;
    
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == 27 && i + 1 < input.length() && input[i + 1] == '[') {
            // Skip the ESC and [
            i += 2;
            // Skip everything until we find a letter
            while (i < input.length() && !isalpha(input[i])) {
                i++;
            }
            if (i < input.length() && isalpha(input[i])) {
                i++;
            }
            i--;
        }
        // Check for other control characters (0-31) but keep space (32)
        else if (c >= 32 && c <= 126) {
            sanitized += c;
        }
    }
    
    return sanitized;
}

void	prompt_search(PhoneBook &book)
{
	int	index;

	book.showContactTable();
	std::cout << "Enter index (0–7) to view full contact details: ";
	std::string index_str;
	std::getline(std::cin, index_str);
	std::stringstream ss(index_str);
	if (!(ss >> index))
	{
		std::cout << "Invalid index." << std::endl;
		return;
	}

    book.showContact(index);
}

void	prompt_contact(PhoneBook &book)
{
	unsigned long long	phone_number;
	Contact				contact;

	std::string first_name, last_name, nickname, darkest_secret,
		phone_number_str;
	phone_number = 0;
	std::cout << "Enter first name: ";
	std::getline(std::cin, first_name);
	first_name = sanitizeInput(first_name);
	std::cout << "Enter last name: ";
	std::getline(std::cin, last_name);
	last_name = sanitizeInput(last_name);
	std::cout << "Enter nickname: ";
	std::getline(std::cin, nickname);
	nickname = sanitizeInput(nickname);
	std::cout << "Enter phone number (digits only): ";
	std::getline(std::cin, phone_number_str);
	std::stringstream ss(phone_number_str);
	if (!(ss >> phone_number))
	{
		std::cout << "Invalid phone number. Setting to 0." << std::endl;
		phone_number = 0;
	}
	std::cout << "Enter darkest secret: ";
	std::getline(std::cin, darkest_secret);
	darkest_secret = sanitizeInput(darkest_secret);
	contact.setContact(first_name, last_name, nickname, phone_number,
		darkest_secret);
	book.addContact(contact);
	std::cout << "Contact added!" << std::endl;
}

bool	isValidCommand(const std::string& cmd)
{
	return (cmd == "ADD" || cmd == "SEARCH" || cmd == "EXIT");
}

int	main(void)
{
	PhoneBook phonebook;
	while (true)
	{
		std::string ans;
		std::cout << "Enter a command (ADD, SEARCH, EXIT):" << std::endl;
		if (!std::getline(std::cin, ans)) {
			std::cout << "\nEOF detected. Exiting..." << std::endl;
			break;
		}
		if (!isValidCommand(ans)) {
			std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT." << std::endl;
			continue;
		}
		if (ans == "ADD")
			prompt_contact(phonebook);
		else if (ans == "SEARCH")
			prompt_search(phonebook);
		else if (ans == "EXIT")
			break ;
		else
			std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT." << std::endl;
	}
	return (0);
}
