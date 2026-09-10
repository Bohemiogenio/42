#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
    private:
        std::string _name;
    public:
        Zombie(std::string name); //Contructor that creates a zombie with a name
        ~Zombie(); //Destroy the zombie
        void announce(void); //Talk about the zombie
};
Zombie* newZombie( std::string name );
void    randomChump( std::string name );

#endif