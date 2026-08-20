#include "PhoneBook.hpp"
#include <iostream>
#include <cstdlib>

static std::string getInput(std::string const &prompt)
{
	std::string input;

	std::cout << prompt;
	std::getline(std::cin, input);
	while (input.empty())
	{
		std::cout << prompt;
		std::getline(std::cin, input);
	}
	return input;
}

static void addContact(PhoneBook &phoneBook)
{
	Contact contact;

	contact.setFirstName(getInput("First name: "));
	contact.setLastName(getInput("Last name: "));
	contact.setNickname(getInput("Nickname: "));
	contact.setPhoneNumber(getInput("Phone number: "));
	contact.setDarkestSecret(getInput("Darkest secret: "));
	phoneBook.addContact(contact);
}

int main(void)
{
	PhoneBook phoneBook;
	std::string command;

	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, command);
		if (command == "ADD")
			addContact(phoneBook);
		else if (command == "SEARCH")
		{
			phoneBook.displayContacts();
			int index = std::atoi(getInput("Enter index: ").c_str());
			phoneBook.displayContact(index);
		}
		else if (command == "EXIT")
			break;
	}
	return 0;
}
