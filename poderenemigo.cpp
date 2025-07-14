#include "poderenemigo.h"
#include "jugador.h"
#include "qgraphicsscene.h"
#include <QtMath>
#include <QList>

PoderEnemigo::PoderEnemigo(QPointF origen, QPointF destino, float velocidad, QGraphicsScene* escena, Jugador* objetivo)
    : velocidad(velocidad), escenaRef(escena), jugadorObjetivo(objetivo) {

    setPixmap(QPixmap(":/images/poder_enemigo.png").scaled(40, 40));
    setPos(origen);
    escena->addItem(this);

    float dx = destino.x() - origen.x();
    float dy = destino.y() - origen.y();
    float mag = qSqrt(dx*dx + dy*dy);
    direccion = QPointF(dx / mag, dy / mag);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PoderEnemigo::mover);
    timer->start(16);
}

void PoderEnemigo::mover() {
    moveBy(direccion.x() * velocidad, direccion.y() * velocidad);

    if (collidesWithItem(jugadorObjetivo)) {
        // Aplicar empuje solo si está en el Nivel 2
        if (jugadorObjetivo->estaEnNivel2) {
            qreal direccion = (x() < jugadorObjetivo->pos().x()) ? 20.0 : -20.0;
            jugadorObjetivo->moveBy(direccion, 0);
        }

        jugadorObjetivo->recibirGolpe();

        escenaRef->removeItem(this);
        deleteLater();
        return;
    }

    // por si sale del área
    if (x() < 0 || x() > 800 || y() < 0 || y() > 600) {
        escenaRef->removeItem(this);
        deleteLater();
    }
}

