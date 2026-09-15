#include "Harl.hpp"

void Harl::debug(void)
{
	std::cout << "[DEBUG] I love having extra bacon..." << std::endl;
}

void Harl::info(void)
{
	std::cout << "[INFO] I cannot belive adding extra bacon costs more money..." << std::endl;
}
void Harl::warning(void)
{
	std::cout << "[WARNING] I think I deserve to have some extra bacon for free..." << std::endl;
}
void Harl::error(void)
{
	std::cout << "[ERROR] This is unacceptable! I want to speak to the manager now." << std::endl;
}
void Harl::complain(std::string level)
{
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*functions[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	for(int i = 0; i < 4; i++;)
	{
		if (level == levels[i])
		{
			(this->*functions[i])();
			return;
		}
	}
}