#include "nivel2.h"
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPixmap>

Nivel2::Nivel2(QGraphicsView* vista)
    : vista(vista) {

    // Crear y configurar la escena
    escena = new QGraphicsScene();
    vista->setScene(escena);
    vista->setSceneRect(0, 0, 800, 600);
    vista->setBackgroundBrush(QBrush(Qt::black));
    vista->setFixedSize(800, 600);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Fondo (temporal o definitivo)
    QPixmap fondo(":/images/fondo_nivel2.png");  // ← agregalo al .qrc
    if (fondo.isNull()) {
        qDebug() << "No se pudo cargar fondo_nivel2.png";
    }

    QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondo.scaled(800, 600));
    fondoItem->setZValue(-1);

    // Jugador
    jugador = new Jugador();
    jugador->setPos(100, 400);
    escena->addItem(jugador);
    jugador->inicializarCorazones();

    // Enemigo nuevo
    enemigo = new HombreEnmascarado(600, 400);
    escena->addItem(enemigo);
    enemigo->inicializarCorazones();

    // Físicas y colisiones
    temporizadorFisicas = new QTimer(this);
    temporizadorColisiones = new QTimer(this);
}

Nivel2::~Nivel2() {
    delete escena;
}

void Nivel2::iniciar() {
    // Movimiento automático del enemigo
    connect(temporizadorFisicas, &QTimer::timeout, [this]() {
        enemigo->mover();
    });
    temporizadorFisicas->start(30);  // velocidad de refresco

    // Futuro: detección de colisiones, físicas avanzadas, etc.

}

Jugador* Nivel2::getJugador() const {
    return jugador;
}
