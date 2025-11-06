#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; i++)
        materias[i] = 0;
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; i++)
        delete materias[i];
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
    for (int i = 0; i < 4; i++)
        materias[i] = 0;
    *this = other;
}
MateriaSource &MateriaSource::operator=(const MateriaSource& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; i++)
        {
            delete materias[i];
            materias[i] = other.materias[i] ? other.materias[i]->clone() : 0;
        }
    }
    return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
    if (!m) return;
    for (int i = 0; i < 4; i++)
    {
        if (!materias[i])
        {
            materias[i] = m->clone(); // stores a clone
            delete m;
            return;
        }
    }
    delete m;
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
    for (int i = 0; i < 4; i++)
    {
        if (materias[i] && materias[i]->getType() == type)
            return materias[i]->clone();
    }
    return 0;
}
