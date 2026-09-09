/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 14:02:36 by Raulsanc          #+#    #+#             */
/*   Updated: 2026/08/20 14:08:10 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <string>

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	std::string phrase;
	for (int i = 1; i < ac; i++)
	{
		if (i > 1)
			phrase += " ";
		phrase += av[i];
	}
	for (size_t i = 0; i < phrase.length(); i++)
				phrase[i] = std::toupper(phrase[i]);
	std::cout << phrase << std::endl;
	return (0);
}
