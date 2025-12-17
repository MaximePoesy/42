#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <exception>
# include <iostream>

class AForm;

class Bureaucrat
{
  private:
	std::string const name;
	int grade;
  public:
	Bureaucrat();
	Bureaucrat(std::string);
	Bureaucrat(std::string, int);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);

	std::string const &getName() const;
	int getGrade() const;
	void incrGrade();
	void decrGrade();
	void signForm(AForm& f);
	void executeForm(AForm const & form) const;

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

std::ostream &operator<<(std::ostream& os, const Bureaucrat& b);
#endif
