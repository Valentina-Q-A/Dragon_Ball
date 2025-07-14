#include "enemigo.h"
#include <QGraphicsPixmapItem>
#include <QObject>

Enemigo::Enemigo(float x, float y, Fisica* fisica, QObject* parent)
    : QObject(parent), QGraphicsPixmapItem(), x(x), y(y), vx(0), vy(0), fisica(fisica) {
    setPos(x, y);
}


Enemigo::~Enemigo() {
    delete fisica;
}

void Enemigo::setPosicion(float nx, float ny) {
    x = nx;
    y = ny;
    setPos(x, y);
}

QPointF Enemigo::getPosicion() const {
    return QPointF(x, y);
}
