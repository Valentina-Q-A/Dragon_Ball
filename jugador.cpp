#include "Jugador.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "../fisicas/SaltoParabolico.h"




Jugador::Jugador(QObject *parent)
    : QObject(parent), vidas(3), energia(100), golpesAcertados(0), enSalto(false), ultimaDireccion(Abajo) {

    QPixmap spriteSheet(":/images/goku.png");
    frameDerecha = spriteSheet.copy(0, 0, 64, 64);
    frameIzquierda = spriteSheet.copy(0, 64, 64, 64);


    // Coordenadas de ejemplo: ajustalas según tu sprite
    frameDerecha   = spriteSheet.copy(  0,  0, 341, 512);
    frameIzquierda = spriteSheet.copy( 682,  512, 341, 512);

    setPixmap(frameDerecha.scaled(120, 120));
    setPos(100, 300);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    // Inicializar física de salto
    //salto = new SaltoParabolico(25.2f, 9.8f, 1.2f);  // v0, g, duración máxima
    salto = new SaltoParabolico(40.0f, 40.0f, 0.5f);  // v0, g, duración

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

void Jugador::saltar() {
    movimientoActivo = false;
    if (!enSalto) {
        enSalto = true;
        salto->aplicar(this);  // se libera automáticamente al aterrizar
    }
}

void Jugador::atacar() {
    // Animación de ataque o efecto de golpe (a implementar)
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
        ultimaDireccion = Arriba;
        setPixmap(frameArriba.scaled(120, 120));
        break;
    case Qt::Key_Down:
        ultimaDireccion = Abajo;
        setPixmap(frameAbajo.scaled(120, 120));
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






