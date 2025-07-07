#include "SaltoParabolico.h"
#include "../personajes/jugador.h"
#include <QDebug>

SaltoParabolico::SaltoParabolico(float velocidadInicial, float gravedad, float duracionMaxima)
    : QObject(), Fisica("SaltoParabolico", velocidadInicial),
    jugador(nullptr), tiempo(0), v0(velocidadInicial), g(gravedad), duracionMaxima(duracionMaxima) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SaltoParabolico::actualizarSalto);
}

void SaltoParabolico::aplicar(Jugador* j) {
    if (estaActiva()) return;

    jugador = j;
    y0 = j->y();
    direccionX = 0;
    if (jugador->movimientoActivo) {
        if (jugador->ultimaDireccion == Jugador::Izquierda) direccionX = -1;
        if (jugador->ultimaDireccion == Jugador::Derecha)  direccionX = 1;
    }
    vX = 6.5f;
    tiempo = 0;
    activar();
    timer->start(10);
}

void SaltoParabolico::actualizarSalto() {
    tiempo += 0.01f;

    float y = y0 - (v0 * tiempo - 0.5f * g * tiempo * tiempo);
    float x = jugador->x() + direccionX * vX;
    qDebug() << "y: " << y;
    qDebug() << "x: " << x;

    if (y >= y0) {
        jugador->setPos(x, y0);
        desactivar();
        jugador->setEnSalto(false);
        timer->stop();
        return;
    }

    jugador->setPos(x, y);
}
