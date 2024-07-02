#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>

class Complex {
    private:
        double real;
        double imag;
    public:
        Complex();
        Complex(double real, double imag);
        Complex(const Complex &c);
        ~Complex(){}
        double getReal() const{return real;}
        double getImag() const{return imag;}
        void setReal(double real){this->real = real;}
        void setImag(double imag){this->imag = imag;}
        bool operator<(const Complex &c) const;
        bool operator>(const Complex &c) const;
        bool operator<=(const Complex &c) const;
        bool operator>=(const Complex &c) const;
        Complex operator=(const Complex &c);
        bool operator==(const Complex &c) const;
        bool operator!=(const Complex &c) const;
        friend std::ostream &operator<<(std::ostream &out, const Complex &c);



};

#endif // COMPLEX_HPP