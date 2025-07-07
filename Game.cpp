#include "Game.h"
#include <QBrush>
#include <QPixmap>
#include <QKeyEvent>

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Game::start() {
    nivel1 = new Nivel1(this);  // Le pasa la vista actual (Game)
    nivel1->iniciar();          // Inicia los temporizadores del nivel
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    qDebug() << "Game tiene foco?" << this->hasFocus();  // ← debe imprimir true
}

void Game::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Tecla presionada:" << event->key();
    if (nivel1 && nivel1->getJugador()) {
        nivel1->getJugador()->keyPressEvent(event);
    }
}

/*void Game::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Tecla soltada:" << event->key();  // ← debug opcional
    if (nivel1 && nivel1->getJugador()) {
        nivel1->getJugador()->keyReleaseEvent(event);
    }
}*/

