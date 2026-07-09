/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:25:20 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/26 14:11:32 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_CPP
#define HARL_CPP

#include <string>

class Harl
{
	private:
		std::string	filter;
		void		debug(void);
		void		info(void);
		void		warning(void);
		void		error(void);
	public:
		void		complain(std::string level);
		void		setFilter(std::string warning);
};

#endif
