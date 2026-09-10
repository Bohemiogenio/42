#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream> //library for input/output operations
#include <string> //library for using std::string

class Zombie {
    private:
        std::string _name;
    public:
        Zombie(); // Default constructor
        Zombie(std::string name); // Constructor with name parameter
        ~Zombie(); // Destructor
        void announce(void); // Announce the zombie's presence
        void setName(std::string name); // Set the zombie's name
};

Zombie* zombieHorde( int N, std::string name );

#endif