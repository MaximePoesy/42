/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:11:32 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 13:34:03 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include "Contact.hpp"

class PhoneBook
{
private :
    Contact con[8];
    int index;
    int	count;

public:
    PhoneBook();
    void	addContact(Contact& contact);
    void	showContactTable();
    void	showContact(int index);
};

#endif
