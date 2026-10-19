#include "Point.hpp"

/*
** Producto vectorial de (b - a) y (p - a).
** El signo indica a qué lado de la recta a->b está p:
**   > 0 : a la izquierda
**   < 0 : a la derecha
**   = 0 : justo encima de la recta
*/
static Fixed	side(Point const &a, Point const &b, Point const &p)
{
	return (b.getX() - a.getX()) * (p.getY() - a.getY())
		- (b.getY() - a.getY()) * (p.getX() - a.getX());
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed const	zero(0);
	Fixed const	d1 = side(a, b, point);
	Fixed const	d2 = side(b, c, point);
	Fixed const	d3 = side(c, a, point);

	// Sobre un lado o un vértice: no cuenta como dentro
	if (d1 == zero || d2 == zero || d3 == zero)
		return false;

	// Dentro si está al mismo lado de las tres aristas
	bool	allPositive = (d1 > zero && d2 > zero && d3 > zero);
	bool	allNegative = (d1 < zero && d2 < zero && d3 < zero);

	return allPositive || allNegative;
}
