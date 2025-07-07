#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsItem>
#include "../fisicas/fisica.h"

class Enemigo : public QGraphicsItem {
protected:
    float x, y;
    float vx, vy;
    Fisica* fisica;

public:
    Enemigo(float x, float y, Fisica* fisica);
    virtual ~Enemigo();

    virtual void mover() = 0;
    virtual void actualizarFisica() = 0;
    virtual void dibujar(QPainter* painter) = 0;

    // Métodos comunes
    void setPosicion(float x, float y);
    QPointF getPosicion() const;
};

#endif // ENEMIGO_H
