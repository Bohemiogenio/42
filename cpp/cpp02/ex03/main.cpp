#include <iostream>
#include "Point.hpp"

static void	test(const char *label, Point const &a, Point const &b,
				Point const &c, Point const &p, bool expected)
{
	bool	result = bsp(a, b, c, p);

	std::cout << (result == expected ? "[OK] " : "[KO] ")
		<< label << " -> " << (result ? "dentro" : "fuera") << std::endl;
}

int main(void)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(0.0f, 10.0f);

	std::cout << "Triángulo: (0,0) (10,0) (0,10)\n" << std::endl;

	test("Punto interior (2, 2)       ", a, b, c, Point(2.0f, 2.0f), true);
	test("Punto interior (1.5, 3.25)  ", a, b, c, Point(1.5f, 3.25f), true);
	test("Punto exterior (8, 8)       ", a, b, c, Point(8.0f, 8.0f), false);
	test("Punto exterior (-1, 5)      ", a, b, c, Point(-1.0f, 5.0f), false);
	test("Vértice (0, 0)              ", a, b, c, Point(0.0f, 0.0f), false);
	test("Vértice (10, 0)             ", a, b, c, Point(10.0f, 0.0f), false);
	test("Sobre un lado (5, 0)        ", a, b, c, Point(5.0f, 0.0f), false);
	test("Sobre la hipotenusa (5, 5)  ", a, b, c, Point(5.0f, 5.0f), false);
	test("Orden inverso de vértices   ", c, b, a, Point(2.0f, 2.0f), true);

	return 0;
}
