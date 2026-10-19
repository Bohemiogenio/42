#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed{
    private:
        int _value;
        static const int _fractionalBits = 8;

    public:
        Fixed(void); //constructeur por defecto
        Fixed(const Fixed &other); //constructor de copia
        Fixed &operator=(const Fixed &other); //Operador de asignacion
        ~Fixed(void); //Destructor

        int getRawBits(void) const; //getter
        void setRawBits(int const raw); //setter
};

#endif