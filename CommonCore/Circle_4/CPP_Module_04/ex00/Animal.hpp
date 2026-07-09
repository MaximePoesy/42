#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal
{
  protected:
	std::string type;
  public:
	Animal();
	~Animal();
	Animal(const Animal &other);
	Animal &operator=(const Animal &other);
	virtual void makeSound() const;
	std::string getType() const;
};

#endif
