#include "nivel1.h"
#include <QGraphicsRectItem>
#include "../personajes/jugador.h"

Nivel1::Nivel1(QGraphicsView* vista)
    : vista(vista) {

    // Crear escena y asociarla a la vista (Game)
    escena = new QGraphicsScene();
    vista->setScene(escena);
    vista->setSceneRect(0, 0, 800, 600);
    vista->setBackgroundBrush(QBrush(Qt::black));
    vista->setFixedSize(800, 600);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Fondo del nivel
    QPixmap fondo(":/images/fondo_nivel1.png");
    QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondo.scaled(800, 600));
    fondoItem->setZValue(-1);  // Asegura que esté detrás de todo


    // Jugador
    jugador = new Jugador();
    jugador->setPos(100, 400);
    escena->addItem(jugador);

    // Enemigo invisible
    enemigo = new HombreInvisible(500, 400);
    escena->addItem(enemigo);

    // Movimiento oscilatorio
    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, [this]() {
        enemigo->mover();
    });

    // Visibilidad periódica
    temporizadorVisibilidad = new QTimer(this);
    connect(temporizadorVisibilidad, &QTimer::timeout, [this]() {
        enemigo->activarVisibilidadTemporal(1000);
    });

}

Nivel1::~Nivel1() {
    delete escena;
}

void Nivel1::iniciar() {
    temporizadorMovimiento->start(16);
    temporizadorVisibilidad->start(3000);
    //temporizadorJugador->start(16);
}

Jugador* Nivel1::getJugador() const {
    return jugador;
}
