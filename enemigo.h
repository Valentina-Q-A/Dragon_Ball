#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "../fisicas/fisica.h"

class Enemigo : public QObject, public QGraphicsPixmapItem  {
    Q_OBJECT
protected:
    float x, y;
    float vx, vy;
    Fisica* fisica;

public:
    Enemigo(float x, float y, Fisica* fisica, QObject* parent = nullptr);
    virtual ~Enemigo();

    virtual void mover() = 0;
    virtual void actualizarFisica() = 0;
    //virtual void dibujar(QPainter* painter) = 0;

    // Métodos comunes
    void setPosicion(float x, float y);
    QPointF getPosicion() const;
};

#endif // ENEMIGO_H
