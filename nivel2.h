#ifndef NIVEL2_H
#define NIVEL2_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "../personajes/jugador.h"
#include "../personajes/hombreenmascarado.h"

class Nivel2 : public QObject {
    Q_OBJECT

public:
    Nivel2(QGraphicsView* vista);
    ~Nivel2();

    void iniciar();
    Jugador* getJugador() const;

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    Jugador* jugador;
    HombreEnmascarado* enemigo;

    QTimer* temporizadorFisicas;
    QTimer* temporizadorColisiones;
};

#endif // NIVEL2_H
