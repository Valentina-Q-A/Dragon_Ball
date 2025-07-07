#ifndef MOVIMIENTOOSCILATORIO_H
#define MOVIMIENTOOSCILATORIO_H

#include "fisica.h"

class MovimientoOscilatorio : public Fisica {
private:
    float xBase;
    float amplitud;
    float frecuencia;
    float tiempo;

public:
    MovimientoOscilatorio(float xBase, float amplitud, float frecuencia);

    void aplicar(Jugador* j) override {}         // No se usa en jugador
    void aplicar(Enemigo* e) override {}         // No se usa en modo directo
    void aplicarFisica(float& x, float& y, float& vx, float& vy) override;
};

#endif // MOVIMIENTOOSCILATORIO_H
