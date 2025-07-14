#include "hombreenmascarado.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include "jugador.h"
#include "../personajes/poderenemigo.h"


HombreEnmascarado::HombreEnmascarado(float x, float y)
    : Enemigo(x, y, nullptr), energiaMaxima(100), energia(100), vidas(3) {

    QPixmap spriteSheet(":/images/enemigo_nivel2.png");
    if (spriteSheet.isNull()) {
        qDebug() << "No se pudo cargar fondo_nivel2.png";
    }

    frameDerecha   = spriteSheet.copy(0, 0, 47, 45);
    frameIzquierda = spriteSheet.copy(229, 63, 47, 45);
    setPixmap(frameDerecha.scaled(240, 240));

    barraEnergia = new QGraphicsRectItem(0, 0, 100, 10);
    barraEnergia->setBrush(Qt::green);
    barraEnergia->setZValue(1);
    barraEnergia->setParentItem(this);
    barraEnergia->setPos(10, -15);

    direccionX = 1;
    direccionY = 0;
    QTimer* timerAtaque = new QTimer(this);
    connect(timerAtaque, &QTimer::timeout, [this]() {
        QList<QGraphicsItem*> items = scene()->items();
        for (QGraphicsItem* item : items) {
            Jugador* jugador = dynamic_cast<Jugador*>(item);
            if (jugador) {
                auto* poder = new PoderEnemigo(this->pos(), jugador->pos(), 7.0f, scene(), jugador);
                break;
            }
        }
    });
    timerAtaque->start(2500); // ataca cada 2.5 segundos
}

HombreEnmascarado::~HombreEnmascarado() {}

void HombreEnmascarado::mover() {
    float nuevoX = x + direccionX * 2;
    float nuevoY = y + direccionY * 2;

    // Solo se limita si está caminando solo
    if (direccionX != 0 || direccionY != 0) {
        // Limita dentro de areaPlataforma si es movimiento autónomo de resto no
        nuevoX = qBound(areaSegura.left(), nuevoX, areaSegura.right() - boundingRect().width());
        nuevoY = qBound(areaSegura.top(), nuevoY, areaSegura.bottom() - boundingRect().height());
    }
    x = nuevoX;
    y = nuevoY;
    actualizarFisica();
    if (direccionX > 0)
        setPixmap(frameDerecha.scaled(120, 120));
    else if (direccionX < 0)
        setPixmap(frameIzquierda.scaled(120, 120));

    if (rand() % 60 == 0) {
        direccionX *= -1;  // Rebota
        direccionY = (rand() % 3 - 1);
        }
    setPosicion(x, y);
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
            msgBox.setText("Has derrotado a Gohan Enmascarado.\n¿Salir?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Salir");
            msgBox.setButtonText(QMessageBox::No, "Salir");
            int result = msgBox.exec();

            if (result == QMessageBox::Yes)
                QApplication::quit();
            else
                qDebug() << "Cargar Nivel 3 para un futuro";
        }
    }
}


void HombreEnmascarado::verificarCaida() {
    if (!areaSegura.contains(pos())) {
        qDebug() << "¡Noo Son Gohan cayó!";
        vidas--;
        actualizarCorazones();
        if (vidas <= 0) {
            QMessageBox::information(nullptr, "Victoria", "¡Has derrotado a Gohan haciéndolo caer!");
            QApplication::quit();
        } else {
            setPos(300, 400);  // reinicia sobre la plataforma
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
