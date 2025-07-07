#include "enemigo.h"

Enemigo::Enemigo(float x, float y, Fisica* fisica)
    : x(x), y(y), vx(0), vy(0), fisica(fisica) {}

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
