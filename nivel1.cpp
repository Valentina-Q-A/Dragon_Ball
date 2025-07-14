#include "nivel1.h"
#include <QGraphicsRectItem>
#include "../personajes/jugador.h"
#include "../control/Game.h"
#include "../personajes/poder.h"
#include "../personajes/poderenemigo.h"


Nivel1::Nivel1(QGraphicsView* vista)
    : vista(vista) {

    escena = new QGraphicsScene();
    vista->setScene(escena);
    vista->setSceneRect(0, 0, 800, 600);
    vista->setBackgroundBrush(QBrush(Qt::black));
    vista->setFixedSize(800, 600);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap fondo(":/images/fondo_nivel1.png");
    QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondo.scaled(800, 600));
    fondoItem->setZValue(-1);

    jugador = new Jugador();
    jugador->setPos(100, 400);
    escena->addItem(jugador);
    jugador->inicializarCorazones();

    enemigo = new HombreInvisible(400, 300, vista);
    escena->addItem(enemigo);
    enemigo->inicializarCorazones();

    //CONEXIÓN CLAVE PARA CAMBIAR NIVEL
    connect(enemigo, &HombreInvisible::nivelCompletado, vista, [this, vista]() {
        Game* game = qobject_cast<Game*>(vista);
        if (game) {
            game->cambiarANivel2();
        }
    });

    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, [this]() {
        if (enemigo) enemigo->mover();
    });

    temporizadorVisibilidad = new QTimer(this);
    connect(temporizadorVisibilidad, &QTimer::timeout, [this]() {
        if (enemigo) enemigo->activarVisibilidadTemporal(1000);
    });
}

Nivel1::~Nivel1() {
    limpiar();
    delete escena;
}

Jugador* Nivel1::getJugador() const {
    return jugador;
}

void Nivel1::iniciar() {
    temporizadorMovimiento->start(16);
    temporizadorVisibilidad->start(3000);
}

// void Nivel1::limpiar() {
//     if (temporizadorMovimiento) temporizadorMovimiento->stop();
//     if (temporizadorVisibilidad) temporizadorVisibilidad->stop();

//     // Detener cualquier otro QTimer que exista en jugador o enemigo
//     if (enemigo) {
//         enemigo->disconnect();  // ← IMPORTANTE: cortar señales activas
//         delete enemigo;
//         enemigo = nullptr;
//     }

//     if (jugador) {
//         jugador->disconnect();
//         delete jugador;
//         jugador = nullptr;
//     }

//     // Eliminar poderes (si quedaran flotando)
//     for (QGraphicsItem* item : escena->items()) {
//         if (dynamic_cast<Poder*>(item) || dynamic_cast<PoderEnemigo*>(item)) {
//             escena->removeItem(item);
//             delete item;
//         }
//     }

//     escena->clear();  // Limpieza visual final
// }

void Nivel1::limpiar() {
    // Detener temporizadores del nivel
    if (temporizadorMovimiento) temporizadorMovimiento->stop();
    if (temporizadorVisibilidad) temporizadorVisibilidad->stop();

    // Eliminar enemigo
    if (enemigo) {
        enemigo->disconnect();  // Previene llamadas desde timers o señales
        if (enemigo->scene()) enemigo->scene()->removeItem(enemigo);
        enemigo->deleteLater();
        enemigo = nullptr;
    }

    // Eliminar jugador
    if (jugador) {
        jugador->disconnect();
        if (jugador->scene()) jugador->scene()->removeItem(jugador);
        jugador->deleteLater();
        jugador = nullptr;
    }

    // Eliminar cualquier poder o poder enemigo que haya quedado
    for (QGraphicsItem* item : escena->items()) {
        Poder* poder = dynamic_cast<Poder*>(item);
        PoderEnemigo* poderE = dynamic_cast<PoderEnemigo*>(item);

        if (poder || poderE) {
            if (item->scene() == escena) {
                item->scene()->removeItem(item);
            }
            QObject* obj = dynamic_cast<QObject*>(item);
            if (obj) {
                obj->disconnect();  // desconecta señales (como QTimer)
                obj->deleteLater(); // elimina de forma segura
            } else {
                delete item; // respaldo en caso de que no herede de QObject
            }
        }
    }

    // Limpieza final de la escena
    escena->clear();  // ← Esto borra lo que quede visualmente
}
