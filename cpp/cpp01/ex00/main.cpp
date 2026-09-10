#include "Zombie.hpp"

int  main(void)
{
    {
        Zombie sova("Sova");
        sova.announce();
    }
    randomChump("Kayo");
    Zombie* miZombie = newZombie("Cypher");
    miZombie->announce();
    delete miZombie;
    
    return 0;
}