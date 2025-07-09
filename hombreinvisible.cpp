#include "hombreinvisible.h"
#include "../fisicas/movimientooscilatorio.h"
#include <cstdlib>

#include <QGraphicsScene>

HombreInvisible::HombreInvisible(float x, float y)
    : Enemigo(x, y, new MovimientoOscilatorio(x, 50, 0.05)), visible(false) {

    //Direcciones aleatorias
    direccionX = (rand() % 3) - 1; // -1, 0, 1
    direccionY = (rand() % 3) - 1; // -1, 0, 1


    // Cargar sprite
    QPixmap spriteSheet(":/images/enemigo_nivel1.png");
    frameDerecha = spriteSheet.copy(0, 0, 341, 256);
    frameIzquierda = spriteSheet.copy(341, 512, 341, 256);

    // Mostrar inicialmente el frameDerecha
    setPixmap(frameDerecha);
    setPixmap(frameDerecha.scaled(120, 120));  // o 100x100 más pequeño
    setPixmap(frameIzquierda.scaled(120, 120));  // o 100x100 más pequeño


    temporizadorVisibilidad = new QTimer(this);
    connect(temporizadorVisibilidad, &QTimer::timeout, [this]() {
        visible = false;
        setVisible(false); //oculta sprite
    });

    setPosicion(x, y);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    // Inicialmente invisible
    //setVisible(false);
}

HombreInvisible::~HombreInvisible() {

}

void HombreInvisible::mover() {
    // Movimiento aleatorio limitado en la plataforma
    if (vx == 0) vx = 0.1;

    // Cambio aleatorio de dirección de vez en cuando
    if (rand() % 30 == 0) {  // Cambia dirección cada ~0.5 segundos (si el timer es 16 ms)
        direccionX = (rand() % 3) - 1; // -1, 0, 1
        direccionY = (rand() % 3) - 1;
    }

    // Actualizar posición según dirección
    x += direccionX * 2 + vx;
    y += direccionY * 2;

    // Limitar al rango de pantalla (ajustar al tamaño real del sprite)
    int anchoSprite = 120;
    int altoSprite = 120;
    x = qBound(0.0f, x, 800.0f - anchoSprite);
    y = qBound(350.0f, y, 600.0f - altoSprite);

    // Aplicar física adicional
    actualizarFisica();
    setPosicion(x, y);

    // Actualizar sprite según dirección X
    if (direccionX > 0)
        setPixmap(frameDerecha.scaled(120, 120));
    else if (direccionX < 0)
        setPixmap(frameIzquierda.scaled(120, 120));
}



void HombreInvisible::actualizarFisica() {
    if (fisica) fisica->aplicarFisica(x, y, vx, vy);
}


void HombreInvisible::activarVisibilidadTemporal(int milisegundos) {
    visible = true;
    // Inicialmente invisible
    setVisible(true);
    temporizadorVisibilidad->start(milisegundos);
}

bool HombreInvisible::estaVisible() const {
    return visible;
}
