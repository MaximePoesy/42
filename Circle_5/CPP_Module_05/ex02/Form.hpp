#ifndef FORM_HPP
# define FORM_HPP
# include <string>
# include <exception>
# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
  private:
	std::string const name;
	bool is_signed;
	int const sign_grade;
	int const exec_grade;

  public:
	Form();
	Form(std::string name, int sign_grade, int exec_grade);
	~Form();
	Form(const Form &other);
	Form &operator=(const Form &other);

	std::string const &getName() const;
	bool getSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	void	beSigned(Bureaucrat &b);

	class GradeTooHighException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char* what() const throw();
	};
};

std::ostream &operator<<(std::ostream& os, const Form& f);

#endif
