#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <exception>
# include <iostream>
# include "Form.hpp"

class Form;

class Bureaucrat
{
  private:
	std::string const name;
	int	grade;
  public:
	Bureaucrat();
	Bureaucrat(std::string);
	Bureaucrat(std::string, int);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);

	std::string const &getName() const;
	int	getGrade() const;
	void	incrGrade();
	void	decrGrade();
	void	signForm(Form& f);

	class	GradeTooHighException : public std::exception
	{
		const char* what() const throw();
	};
	class   GradeTooLowException : public std::exception
        {
                const char* what() const throw();
        };
};

std::ostream &operator<<(std::ostream& os, const Bureaucrat& b);
#endif
