#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
    Zombie* other = new Zombie(name);
    return other;
}