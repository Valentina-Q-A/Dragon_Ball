#ifndef PODERENEMIGO_H
#define PODERENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Jugador;

class PoderEnemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PoderEnemigo(QPointF origen, QPointF destino, float velocidad, QGraphicsScene* escena, Jugador* objetivo);

private slots:
    void mover();

private:
    QTimer* timer;
    QPointF direccion;
    float velocidad;
    QGraphicsScene* escenaRef;
    Jugador* jugadorObjetivo;
};

#endif // PODERENEMIGO_H
