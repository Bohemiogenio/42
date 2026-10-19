#include "Point.hpp"

Point::Point(void) : _x(0), _y(0)
{
}

Point::Point(const float x, const float y) : _x(x), _y(y)
{
}

Point::Point(const Point &other) : _x(other._x), _y(other._y)
{
}

/*
** _x e _y son const: una vez construidos no se pueden modificar.
** Por eso este operador no puede copiar nada; existe solo para cumplir
** la forma canónica ortodoxa.
*/
Point &Point::operator=(const Point &other)
{
	(void)other;
	return *this;
}

Point::~Point(void)
{
}

Fixed Point::getX(void) const
{
	return this->_x;
}

Fixed Point::getY(void) const
{
	return this->_y;
}
