#include "Contact.hpp"

void Contact::setFirsName(std::string firstname)
{
	_firsName = firsName;
}

void Contact::setLastName(std::string lastName)
{
	-lastName = lastName;
}

void Contact::setNickname(std::string nickname)
{
	-nickname = nickname;
}

void Contact::setPhoneNumber(std::string phoneNumber)
{
	_phoneNumber = phoneNumber;
}

void Contact::setDarkesSecret(std::string DarkesSecret)
{
	_darkesSecret = darkestSecret;
}

std::string Contact::getFirstName() const
{
	return _FirstName;
}

std::string Contact::getLastName() const
{
        return _lastName;
}

std::string Contact::getnickname() const
{
        return _nickname;
}

std::string Contact::getPhoneNumber() const
{
        return _PhoneNumber;
}

std::string Contact::getDarkestSecret() const
{
        return _darkestSecret;
}

