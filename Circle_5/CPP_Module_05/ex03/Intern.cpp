#include "Intern.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::~Intern()
{
}

Intern::Intern(const Intern &other)
{
    *this = other;
}

//no attribute, so always true
Intern &Intern::operator=(const Intern &other)
{
    (void)other;
    return *this;
}

AForm* Intern::createShrubbery(std::string const & target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(std::string const & target)
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPardon(std::string const & target)
{
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string formName, std::string target)
{
    // Form names
    std::string formNames[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    // Function pointers
    AForm* (*creators[3])(std::string const &) = {
        &Intern::createShrubbery,
        &Intern::createRobotomy,
        &Intern::createPardon
    };

    for (int i = 0; i < 3; i++)
    {
        if (formNames[i] == formName)
        {
            std::cout << "Intern creates " << formName << std::endl;
            return creators[i](target);
        }
    }

    std::cout << "Error: Form \"" << formName << "\" does not exist" << std::endl;
    return NULL;
}
