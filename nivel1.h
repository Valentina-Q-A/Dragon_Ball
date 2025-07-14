#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include "../personajes/hombreinvisible.h"

class Nivel1 : public QObject {
    Q_OBJECT

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    HombreInvisible* enemigo;
    QTimer* temporizadorMovimiento;
    QTimer* temporizadorVisibilidad;
    Jugador* jugador;

public:
    Nivel1(QGraphicsView* vista);
    ~Nivel1();
    Jugador* getJugador() const;

    void iniciar();
    void limpiar();
};

#endif // NIVEL1_H
