#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("Default Form"), is_signed(false), sign_grade(150), exec_grade(150)
{
}

Form::Form(std::string _name, int _sign_grade, int _exec_grade) 
	: name(_name), is_signed(false), sign_grade(_sign_grade), exec_grade(_exec_grade)
{
	if (sign_grade < 1 || exec_grade < 1)
		throw GradeTooHighException();
	if (sign_grade > 150 || exec_grade > 150)
		throw GradeTooLowException();
}

Form::~Form()
{
}

Form::Form(const Form &other) 
	: name(other.name), is_signed(other.is_signed), 
	  sign_grade(other.sign_grade), exec_grade(other.exec_grade)
{
}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
	{
		this->is_signed = other.is_signed;
		// name, sign_grade, and exec_grade are const
	}
	return (*this);
}

std::string const &Form::getName() const
{
	return name;
}

bool Form::getSigned() const
{
	return is_signed;
}

int Form::getGradeToSign() const
{
	return sign_grade;
}

int Form::getGradeToExecute() const
{
	return exec_grade;
}

void    Form::beSigned(Bureaucrat &b)
{
	if (is_signed)
        	return;
	if (b.getGrade() <= sign_grade)
		is_signed = true;
	else
                throw GradeTooLowException();
}

std::ostream &operator<<(std::ostream& os, const Form& f)
{
	os << "Form " << f.getName() 
	   << ", signed: " << (f.getSigned() ? "yes" : "no")
	   << ", grade required to sign: " << f.getGradeToSign()
	   << ", grade required to execute: " << f.getGradeToExecute();
	return os;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Form grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form grade is too low";
}
