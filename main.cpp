#include <QApplication>
#include "control/Game.h"
#include <QMessageBox>
#include <stdexcept>  // Para runtime_error


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    try {
        Game *game = new Game();
        game->show();
        game->start();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(nullptr, "Error crítico", e.what());
        return -1;
    }

    return a.exec();
}
