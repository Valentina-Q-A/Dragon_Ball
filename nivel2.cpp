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

    // Fondo
    QPixmap fondo(":/images/fondo_nivel2.png");
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

    // Plataforma
    QRectF areaPlataforma(160, 100, 500, 350);  // para cubrir casi hasta la base
    //escena->addRect(areaPlataforma, QPen(Qt::red));  // Dibuja el área de la plataforma

    jugador->setAreaSegura(areaPlataforma);
    enemigo->setAreaSegura(areaPlataforma);

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
    jugador->estaEnNivel2 = true;

    connect(temporizadorColisiones, &QTimer::timeout, [this]() {
        jugador->verificarCaida();
        enemigo->verificarCaida();
    });
    temporizadorColisiones->start(30);
}

Jugador* Nivel2::getJugador() const {
    return jugador;
}
