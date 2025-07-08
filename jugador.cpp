#include "Jugador.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "hombreinvisible.h"

#include "../fisicas/SaltoParabolico.h"




Jugador::Jugador(QObject *parent)
    : QObject(parent), vidas(3), energia(100), golpesAcertados(0), enSalto(false), ultimaDireccion(Abajo) {

    QPixmap spriteSheet(":/images/goku.png");

    // Coordenadas de ejemplo: ajustalas según tu sprite
    frameDerecha   = spriteSheet.copy(  345,  0, 345, 547);
    frameIzquierda = spriteSheet.copy( 345,  547, 345, 547);
    frameArriba   = spriteSheet.copy(  345,  1094, 345, 547);
    frameAbajo   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueDerecha   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueIzquierda   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueAbajo   = spriteSheet.copy(  0,  0, 380, 547);
    frameRecibirDanio = spriteSheet.copy(  0,  0, 380, 547);

    setPixmap(frameDerecha.scaled(120, 120));
    setPos(100, 300);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    // Inicializar física de salto
    //salto = new SaltoParabolico(25.2f, 9.8f, 1.2f);  // v0, g, duración máxima
    salto = new SaltoParabolico(40.0f, 40.0f, 0.5f);  // v0, g, duración

    frameAtaque = QPixmap(":/images/goku_ataque.png"); // ← agregá este sprite a tu proyecto
    timerAtaque = new QTimer(this);
    connect(timerAtaque, &QTimer::timeout, [this]() {
        setPixmap(frameDerecha.scaled(120, 120)); // ← o la última dirección que corresponda
        timerAtaque->stop();
    });


}

void Jugador::moverIzquierda() {
    setX(x() - 10);
    ultimaDireccion = Izquierda;
    setPixmap(frameIzquierda.scaled(120, 120));
    movimientoActivo = true;

}

void Jugador::moverDerecha() {
    setX(x() + 10);
    ultimaDireccion = Derecha;
    setPixmap(frameDerecha.scaled(120, 120));
    movimientoActivo = true;

}

void Jugador::moverArriba() {
    setY(y() - 10);
    ultimaDireccion = Arriba;
    setPixmap(frameArriba.scaled(120, 120));
    movimientoActivo = true;

}

void Jugador::moverAbajo() {
    setY(y() + 10);
    ultimaDireccion = Abajo;
    setPixmap(frameAbajo.scaled(120, 120));
    movimientoActivo = true;

}

void Jugador::saltar() {
    movimientoActivo = false;
    if (!enSalto) {
        enSalto = true;
        salto->aplicar(this);  // se libera automáticamente al aterrizar
    }
}

void Jugador::atacar() {
    setPixmap(frameAtaque.scaled(120, 120));
    timerAtaque->start(300);  // Vuelve al sprite normal luego de 300 ms

    // Buscar enemigo en la escena
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem* item : colisiones) {
        HombreInvisible* enemigo = dynamic_cast<HombreInvisible*>(item);
        if (enemigo && enemigo->estaVisible()) {
            enemigo->setVisible(false);  // Desaparece como si lo golpeara
            // Podés agregar sonido, partículas, puntos, etc.
        }
    }
}


void Jugador::recibirDanio(int cantidad) {
    vidas -= cantidad;
    if (vidas < 0) vidas = 0;
}

void Jugador::reiniciarEstado() {
    vidas = 3;
    energia = 100;
    golpesAcertados = 0;
    setPos(100, 300);
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Jugador recibió tecla:" << event->key();  // ← DEBUG CRÍTICO
    //if (event->isAutoRepeat()) return;  // Ignora repeticiones
    switch (event->key()) {
    case Qt::Key_Left:
        moverIzquierda();
        break;
    case Qt::Key_Right:
        moverDerecha();
        break;
    case Qt::Key_Up:
        moverArriba();
        break;
    case Qt::Key_Down:
        moverAbajo();
        break;
    case Qt::Key_Space:
        saltar();
        break;
    case Qt::Key_X:
        atacar();
        break;
    }
}

void Jugador::setEnSalto(bool valor) {
    enSalto = valor;
}

/*float Jugador::getVelocidad() const {
    return velocidad;
}*/

/*void Jugador::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;  // Ignora repeticiones
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        movimientoActivo = false;
        break;
    }
}*/
