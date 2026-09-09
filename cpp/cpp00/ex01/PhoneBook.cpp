#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : _nbContacts(0), _nextIndex(0)
{
}

void PhoneBook::addContact(Contact const &contact)
{
	_contacts[_nextIndex] = contact;
	_nextIndex = (_nextIndex + 1) % MAX_CONTACTS;
	if (_nbContacts < MAX_CONTACTS)
		_nbContacts++;
}

std::string PhoneBook::_truncate(std::string const &field)
{
	if (field.length() > 10)
		return field.substr(0, 9) + ".";
	return field;
}

void PhoneBook::displayContacts() const
{
	std::cout << std::right << std::setw(10) << "Index" << "|"
		  << std::right << std::setw(10) << "First Name" << "|"
		  << std::right << std::setw(10) << "Last Name" << "|"
		  << std::right << std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < _nbContacts; i++)
	{
		std::ostringstream oss;
		oss << i;

		std::cout << std::right << std::setw(10) << _truncate(oss.str()) << "|"
			  << std::right << std::setw(10) << _truncate(_contacts[i].getFirstName()) << "|"
			  << std::right << std::setw(10) << _truncate(_contacts[i].getLastName()) << "|"
			  << std::right << std::setw(10) << _truncate(_contacts[i].getNickname()) << std::endl;
	}
}

void PhoneBook::displayContact(int index) const
{
	if (index < 0 || index >= _nbContacts)
	{
		std::cout << "invalid index." << std::endl;
		return;
	}
	std::cout << "First Name:     " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name:      " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname:       " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number:   " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
}
