#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm() 
	: AForm("Robotomy Request Form", 72, 45), target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string _target)
	: AForm("Robotomy Request Form", 72, 45), target(_target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other), target(other.target)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->target = other.target;
	}
	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (!getSigned())
		throw FormNotSignedException();
	if (executor.getGrade() > getGradeToExecute())
		throw GradeTooLowException();

	std::cout << "* DRILLING NOISES * WHIRRRRR... *" << std::endl;

	static bool seeded = false;
	if (!seeded)
	{
		std::srand(std::time(0));
		seeded = true;
	}

	if (std::rand() % 2 == 0)
	{
		std::cout << target << " has been robotomized successfully!" << std::endl;
	}
	else
	{
		std::cout << "The robotomy on " << target << " failed." << std::endl;
	}
}
