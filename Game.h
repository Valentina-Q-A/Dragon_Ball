#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "../personajes/Jugador.h"
#include "../niveles/nivel1.h"
#include "../niveles/nivel2.h"

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void start();
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void cambiarANivel2();

private:
    QGraphicsScene *scene;
    Jugador *jugador;
    Nivel1* nivel1;
    Nivel2* nivel2 = nullptr;
};

#endif // GAME_H
