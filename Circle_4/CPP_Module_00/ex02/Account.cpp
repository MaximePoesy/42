/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:10:09 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/24 16:36:13 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

// Static member initialization
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit):  _accountIndex(_nbAccounts), 
					_amount(initial_deposit),
					_nbDeposits(0),
					_nbWithdrawals(0)
{
	_nbAccounts++;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account(void)
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex
		  << ";p_amount:" << _amount
		  << ";deposit:" << deposit;
	_amount += deposit;
	_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;
	std::cout << ";amount:" << _amount
		  << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex
		  << ";p_amount:" << _amount;

	if (withdrawal > _amount)
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	_amount -= withdrawal;
	_nbWithdrawals++;
	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;
	std::cout << ";withdrawal:" << withdrawal
		  << ";amount:" << _amount
		  << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}

int Account::checkAmount(void) const
{
	return (_amount);
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex
		  << ";amount:" << _amount
		  << ";deposits:" << _nbDeposits
		  << ";withdrawals:" << _nbWithdrawals << std::endl;
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << " accounts:" << _nbAccounts
		  << ";total:" << _totalAmount
		  << ";deposits:" << _totalNbDeposits
		  << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::_displayTimestamp(void)
{
	std::time_t now = std::time(NULL);
	std::tm* tm = std::localtime(&now);
	std::cout << "[" << std::setfill('0')
		  << std::setw(4) << tm->tm_year + 1900
		  << std::setw(2) << tm->tm_mon + 1
		  << std::setw(2) << tm->tm_mday << "_"
		  << std::setw(2) << tm->tm_hour
		  << std::setw(2) << tm->tm_min
		  << std::setw(2) << tm->tm_sec << "]";
}
