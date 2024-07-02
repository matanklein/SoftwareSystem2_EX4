#include "complex.hpp"

Complex::Complex() {
    real = 0;
    imag = 0;
}

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

Complex::Complex(const Complex &c) : real(c.real), imag(c.imag) {}

bool Complex::operator<(const Complex &c) const {
    return real*real + imag*imag < c.real*c.real + c.imag*c.imag;
}

bool Complex::operator>(const Complex &c) const {
    return (c < *this);
}

bool Complex::operator<=(const Complex &c) const {
    return !(*this > c);
}

bool Complex::operator>=(const Complex &c) const {
    return !(*this < c);
}

Complex Complex::operator=(const Complex &c) {
    real = c.real;
    imag = c.imag;
    return *this;
}

bool Complex::operator==(const Complex &c) const {
    return (*this >= c) && (*this <= c);
}

bool Complex::operator!=(const Complex &c) const {
    return !(*this == c);
}

std::ostream &operator<<(std::ostream &out, const Complex &c) {
    if(c.imag < 0){
        out << c.real << " - " << -c.imag << "i";
    }else{
        out << c.real << " + " << c.imag << "i";
    }
    return out;
}