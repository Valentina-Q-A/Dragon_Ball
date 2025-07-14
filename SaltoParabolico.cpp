#include "SaltoParabolico.h"
#include "../personajes/jugador.h"
#include <QDebug>

SaltoParabolico::SaltoParabolico(float velocidadInicial, float gravedad, float duracionMaxima)
    : QObject(), Fisica("SaltoParabolico", velocidadInicial),
    jugador(nullptr), tiempo(0), dt(0.01f), y0(0), duracionMaxima(duracionMaxima),
    posicion(), gravedad(gravedad), velocidad(), aceleracion(0, gravedad) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SaltoParabolico::actualizarSalto);
}

void SaltoParabolico::aplicar(Jugador* j) {
    if (estaActiva()) return;

    jugador = j;
    y0 = j->y();
    tiempo = 0;
    dt = 0.01f;

    // Dirección horizontal
    float dirX = 0;
    switch (jugador->getUltimaDireccion()) {
    case Jugador::Izquierda: dirX = -1; break;
    case Jugador::Derecha:   dirX =  1; break;
    default: dirX = 0; break; // Si estaba mirando arriba o abajo, sin movimiento horizontal
    }

    // Fijar velocidades iniciales
    float v_horizontal = 80.0f;       // píxeles por segundo (ajustable)
    float v_vertical = intensidadBase; // intensidadBase ya es la vertical

    velocidad = QVector2D(dirX * v_horizontal, -v_vertical);  // Ojo: negativo porque va hacia arriba


    // Inicializar vectores físicos
    posicion = QVector2D(jugador->x(), jugador->y());
    //velocidad = QVector2D(dirX * 6.5f, -intensidadBase);  // Negativo porque sube
    aceleracion = QVector2D(0, gravedad); // Aceleración hacia abajo



    jugador->setEnSalto(true);
    activar();
    timer->start(int(dt * 1000)); // 10 ms
}


void SaltoParabolico::actualizarSalto() {
    tiempo += dt;

    // Integración tipo Euler
    velocidad += aceleracion * dt;
    posicion += velocidad * dt;

    jugador->setPos(posicion.x(), posicion.y());

    if (posicion.y() >= y0 || tiempo >= duracionMaxima) {
        jugador->setPos(posicion.x(), y0); // Asegura que quede justo sobre el piso
        jugador->setEnSalto(false);
        desactivar();
        timer->stop();
    }
}
