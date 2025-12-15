#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("Default Form"), is_signed(false), sign_grade(150), exec_grade(150)
{
}

AForm::AForm(std::string _name, int _sign_grade, int _exec_grade) 
	: name(_name), is_signed(false), sign_grade(_sign_grade), exec_grade(_exec_grade)
{
	if (sign_grade < 1 || exec_grade < 1)
		throw GradeTooHighException();
	if (sign_grade > 150 || exec_grade > 150)
		throw GradeTooLowException();
}

AForm::~AForm()
{
}

AForm::AForm(const AForm &other) 
	: name(other.name), is_signed(other.is_signed), 
	  sign_grade(other.sign_grade), exec_grade(other.exec_grade)
{
}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		this->is_signed = other.is_signed;
	}
	return (*this);
}

std::string const &AForm::getName() const
{
	return name;
}

bool AForm::getSigned() const
{
	return is_signed;
}

int AForm::getGradeToSign() const
{
	return sign_grade;
}

int AForm::getGradeToExecute() const
{
	return exec_grade;
}

void AForm::beSigned(Bureaucrat &b)
{
	if (is_signed)
		return;
	if (b.getGrade() <= sign_grade)
		is_signed = true;
	else
		throw GradeTooLowException();
}

std::ostream &operator<<(std::ostream& os, const AForm& f)
{
	os << "Form " << f.getName() 
	   << ", signed: " << (f.getSigned() ? "yes" : "no")
	   << ", grade required to sign: " << f.getGradeToSign()
	   << ", grade required to execute: " << f.getGradeToExecute();
	return os;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Form grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Form grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed";
}
