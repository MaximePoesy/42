#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal
{
  protected:
	std::string type;
	Animal(); // <---
  public:
	virtual ~Animal();
	Animal(const Animal &other);
	Animal &operator=(const Animal &other);
	virtual void makeSound() const = 0;
	std::string getType() const;
};

#endif
