#include "hombreenmascarado.h"
//#include "../fisicas/deslizamiento.h"  // futura física a implementar
#include <QGraphicsScene>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

HombreEnmascarado::HombreEnmascarado(float x, float y)
    : Enemigo(x, y, nullptr), energiaMaxima(100), energia(100), vidas(3) {

    QPixmap spriteSheet(":/images/enemigo_nivel2.png");  // Agregalo a .qrc
    if (spriteSheet.isNull()) {
        qDebug() << "No se pudo cargar fondo_nivel2.png";
    }

    frameDerecha   = spriteSheet.copy(0, 0, 256, 256);
    frameIzquierda = spriteSheet.copy(256, 0, 256, 256);
    setPixmap(frameDerecha.scaled(120, 120));

    barraEnergia = new QGraphicsRectItem(0, 0, 100, 10);
    barraEnergia->setBrush(Qt::green);
    barraEnergia->setZValue(1);
    barraEnergia->setParentItem(this);
    barraEnergia->setPos(10, -15);

    direccionX = 1;
    direccionY = 0;
}

HombreEnmascarado::~HombreEnmascarado() {}

void HombreEnmascarado::mover() {
    x += direccionX * 2;
    y += direccionY * 2;

    actualizarFisica();
    setPosicion(x, y);

    if (direccionX > 0)
        setPixmap(frameDerecha.scaled(120, 120));
    else if (direccionX < 0)
        setPixmap(frameIzquierda.scaled(120, 120));

    // Límite de área (puede ajustarse más adelante)
    int ancho = 120;
    int alto = 120;
    x = qBound(0.0f, x, 800.0f - ancho);
    y = qBound(0.0f, y, 600.0f - alto);
}

void HombreEnmascarado::actualizarFisica() {
    if (fisica)
        fisica->aplicarFisica(x, y, vx, vy);
}

void HombreEnmascarado::inicializarCorazones() {
    if (!scene()) return;
    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem* corazon = new QGraphicsPixmapItem(QPixmap(":/images/corazon.png").scaled(25, 25));
        corazon->setZValue(2);
        scene()->addItem(corazon);
        corazon->setPos(700 + i * 30, 10);  // arriba derecha
        corazones.append(corazon);
    }
}

void HombreEnmascarado::actualizarCorazones() {
    for (int i = 0; i < corazones.size(); ++i)
        corazones[i]->setVisible(i < vidas);
}

void HombreEnmascarado::recibirDanio() {
    energia -= 20;
    if (energia < 0) energia = 0;

    float porcentaje = float(energia) / energiaMaxima;
    barraEnergia->setRect(0, 0, 100 * porcentaje, 10);
    if (porcentaje > 0.6)
        barraEnergia->setBrush(Qt::green);
    else if (porcentaje > 0.3)
        barraEnergia->setBrush(Qt::yellow);
    else
        barraEnergia->setBrush(Qt::red);

    if (energia == 0) {
        vidas--;
        actualizarCorazones();

        if (vidas > 0) {
            energia = energiaMaxima;
            barraEnergia->setRect(0, 0, 100, 10);
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("¡Victoria!");
            msgBox.setText("Has derrotado a Gohan Enmascarado.\n¿Salir o pasar al Nivel 3?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Salir");
            msgBox.setButtonText(QMessageBox::No, "Nivel 3");
            int result = msgBox.exec();

            if (result == QMessageBox::Yes)
                QApplication::quit();
            else
                qDebug() << "Cargar Nivel 3 (a implementar)";
        }
    }
}

void HombreEnmascarado::reiniciarEstado() {
    vidas = 3;
    energia = energiaMaxima;
    barraEnergia->setRect(0, 0, 100, 10);
    actualizarCorazones();
    setPos(600, 400);
}
