#ifndef DOG_HPP
# define DOG_HPP

# include <string>
# include "Animal.hpp"
# include "Brain.hpp"

class Dog: public Animal
{
  private:
    	Brain* brain;
  public:
	Dog();
	virtual ~Dog();
	Dog(const Dog &other);
	Dog &operator=(const Dog &other);
	virtual void makeSound() const;
};

#endif
