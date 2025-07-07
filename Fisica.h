#ifndef FISICA_H
#define FISICA_H

#include <QString>

class Jugador;
class Enemigo;

class Fisica {
public:
    Fisica(QString nombre, float intensidadBase);
    virtual ~Fisica() {}

    // Métodos virtuales puros
    virtual void aplicar(Jugador* j) = 0;
    virtual void aplicar(Enemigo* e) = 0;
    virtual void aplicarFisica(float& x, float& y, float& vx, float& vy) = 0;

    void activar() { activa = true; }
    void desactivar() { activa = false; }
    bool estaActiva() const { return activa; }

protected:
    QString nombre;
    float intensidadBase;
    bool activa;
};

#endif // FISICA_H

