#include "Zombie.hpp"

int  main(void)
{
    Zombie* miZombie = newZombie("Cypher");
    miZombie->announce();
    {
        Zombie sova("Sova");
        sova.announce();
    }
    randomChump("Kayo");
    delete miZombie;
    
    return 0;
}