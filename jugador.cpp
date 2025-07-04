#include "Jugador.h"
#include <QPixmap>
#include <QGraphicsScene>

Jugador::Jugador(QObject *parent)
    : QObject(parent), vidas(3), energia(100), golpesAcertados(0),
    velocidad(5.0f), enSalto(false) {

    QPixmap spriteSheet(":/images/goku.png");

    // Ejemplo: si cada cuadro mide 16x16 píxeles
    frameAbajo     = spriteSheet.copy(  0,  0, 329, 493);
    frameIzquierda = spriteSheet.copy( 493,  0, 329, 493);
    frameDerecha   = spriteSheet.copy( 986,  0, 329, 493);
    frameArriba    = spriteSheet.copy( 1479,  350, 329, 493);

    // Mostrar uno por defecto
    setPixmap(frameAbajo.scaled(48, 48));

    //setPixmap(QPixmap(":/images/goku.png").scaled(48, 48));
    setPos(100, 300);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}


void Jugador::moverIzquierda() {
    setX(x() - velocidad);
}

void Jugador::moverDerecha() {
    setX(x() + velocidad);
}

void Jugador::saltar() {
    // Se implementará con física de salto luego
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
