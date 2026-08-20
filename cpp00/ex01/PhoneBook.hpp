#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		static const int MAX_CONTACTS = 8;

		Contact _contacts[MAX_CONTACTS];
		int	_nbContacts;
		int	_nextIndex;

		static std::string _truncate(std::string const /field);
	public:
		PhoneBook();

		void addContact(Contact const &contact);
		void displayContacts() const;
		void displayContact(int index) const;
}

#endif
