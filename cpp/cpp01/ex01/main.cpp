#include "Zombie.hpp"

int main(void)
{
	Zombie* newhorde = zombieHorde(7, "Chamber");

	for(int i = 0; i < 7; i++)
	{
		newhorde[i].announce();
	}

	delete[] newhorde;

	return 0;
}