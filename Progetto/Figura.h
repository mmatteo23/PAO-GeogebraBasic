#ifndef FIGURA_H
#define FIGURA_H

#include "Disegnabile.h"
#include "Punto.h"

class Figura : public Disegnabile {
protected:
    Figura(string ="Figura", string ="#000000");
public:
    virtual double perimetro() const =0;
    virtual double area() const =0;
};

#endif // FIGURA_H
