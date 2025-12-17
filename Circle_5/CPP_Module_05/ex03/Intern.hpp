#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>
# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class Intern
{
	private: 
		//no need to call them
		static AForm* createShrubbery(std::string const & target);
		static AForm* createRobotomy(std::string const & target);
		static AForm* createPardon(std::string const & target);

	public:
		Intern();
		~Intern();
		Intern(const Intern &other);
		Intern &operator=(const Intern &other);
		
		AForm* makeForm(std::string formName, std::string target);
};

#endif
