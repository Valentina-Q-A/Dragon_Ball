#include <QApplication>
#include "control/Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //QGraphicsView vista;

    Game *game = new Game();
    game->show();

    //MIRAR SIN ESTO
    game->start();
    game->setFocus();  // ← Muy importante

    return a.exec();
}
