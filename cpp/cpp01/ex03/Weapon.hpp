#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon{
	private:
		std::string _type;

	public:
		Weapon(std::string type); //Constructor
		const std::string& getType(void) const; //Only read
		void setType(std::string type); //Change type
};


#endif