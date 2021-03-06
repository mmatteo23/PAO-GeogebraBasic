#ifndef LINEA_H
#define LINEA_H

#include "Disegnabile.h"
#include "Punto.h"

class Linea : public Disegnabile {
private:
    std::pair<Punto, Punto> punti;

protected:
    Linea(string, string, Punto*, Punto*);

    Linea(string ="Linea", string ="#000000");
public:
    /**
     * @brief getPunti
     * @return ritorna i punti per cui passa una linea e che la identificano
     */
    const std::pair<Punto, Punto>& getPunti() const;

    ~Linea() =default;

    void setPunti(Punto, Punto);
};

#endif // LINEA_H
