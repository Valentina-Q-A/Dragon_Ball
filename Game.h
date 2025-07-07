#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "../personajes/Jugador.h"
#include "../niveles/nivel1.h"

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    //ESTO NO ESTABA
    void start();
    void keyPressEvent(QKeyEvent* event) override;
    //void keyReleaseEvent(QKeyEvent* event) override;


private:
    QGraphicsScene *scene;
    Jugador *jugador;
    //HASTA AQUI FUNCIONABA
    Nivel1* nivel1;
    //QTimer* timerMovimiento;  // ← NUEVO
/*private slots:
    void actualizarMovimiento();*/
};

#endif // GAME_H
