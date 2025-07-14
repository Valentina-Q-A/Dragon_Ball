#include "Game.h"
#include <QBrush>
#include <QPixmap>
#include <QKeyEvent>

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Game::start() {
    nivel1 = new Nivel1(this);
    nivel1->iniciar();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    qDebug() << "Game tiene foco?" << this->hasFocus();
}

void Game::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Tecla presionada:" << event->key();
    if (nivel1 && nivel1->getJugador()) {
        nivel1->getJugador()->keyPressEvent(event);
    } else if (nivel2 && nivel2->getJugador()) {
        nivel2->getJugador()->keyPressEvent(event);
    }
}

void Game::cambiarANivel2() {
    if (nivel1) {
        nivel1->limpiar();
        delete nivel1;
        nivel1 = nullptr;
    }

    nivel2 = new Nivel2(this);
    nivel2->iniciar();
    setFocus();
}
