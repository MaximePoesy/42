#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Julien")
{
	grade = 50;
}

Bureaucrat::Bureaucrat(std::string _name) : name(_name)
{
	grade = 50;
}

Bureaucrat::Bureaucrat(std::string _name, int _grade) : name(_name)
{
        if (_grade < 1)
		throw GradeTooHighException();
	if (_grade > 150)
		throw GradeTooLowException();
	grade = _grade;
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : name(other.name), grade(other.grade)
{
	*this = other;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		this->grade = other.grade;
	}
	return (*this);
}

std::string const&	Bureaucrat::getName() const
{
	return name;
}

int     Bureaucrat::getGrade() const
{
	return grade;
}

void    Bureaucrat::incrGrade()
{
	if (grade - 1 < 1)
		throw GradeTooHighException();
	grade--;
}

void    Bureaucrat::decrGrade()
{
	if (grade + 1 > 150)
                throw GradeTooLowException();
        grade++;
}

void    Bureaucrat::signForm(Form& f)
{
	f.beSigned(*this);
}

std::ostream &operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade Too High";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
        return "Grade Too Low";
}
