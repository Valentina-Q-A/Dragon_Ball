#include "hombreinvisible.h"
#include "../fisicas/movimientooscilatorio.h"
#include <cstdlib>
#include "jugador.h"
#include "personajes/poderenemigo.h"

#include <QGraphicsScene>

#include <QMessageBox>
#include <QApplication>
#include "../niveles/nivel2.h"


HombreInvisible::HombreInvisible(float x, float y, QGraphicsView* vista)
    : Enemigo(x, y, new MovimientoOscilatorio(x, 50, 0.05)), visible(false), vista(vista) {

    //Direcciones aleatorias
    direccionX = (rand() % 3) - 1; // -1, 0, 1
    direccionY = (rand() % 3) - 1; // -1, 0, 1


    // Cargar sprite
    QPixmap spriteSheet(":/images/enemigo_nivel1.png");
    frameDerecha = spriteSheet.copy(0, 0, 341, 256);
    frameIzquierda = spriteSheet.copy(341, 512, 341, 256);

    // Mostrar inicialmente el frameDerecha
    setPixmap(frameDerecha);
    setPixmap(frameDerecha.scaled(120, 120));  // o 100x100 más pequeño
    setPixmap(frameIzquierda.scaled(120, 120));  // o 100x100 más pequeño


    temporizadorVisibilidad = new QTimer(this);
    connect(temporizadorVisibilidad, &QTimer::timeout, [this]() {
        visible = false;
        setVisible(false); //oculta sprite
    });

    QTimer* timerAtaque = new QTimer(this);
    connect(timerAtaque, &QTimer::timeout, [this]() {
        if (!this->estaVisible()) {
            QList<QGraphicsItem*> items = scene()->items();
            for (QGraphicsItem* item : items) {
                Jugador* jugador = dynamic_cast<Jugador*>(item);
                if (jugador) {
                    QPointF origen = this->pos();
                    QPointF destino = jugador->pos();
                    auto* poder = new PoderEnemigo(origen, destino, 6.0f, scene(), jugador);
                    break;
                }
            }
        }
    });
    timerAtaque->start(2000);  // Ataca cada 2 segundos si está invisible

    setPosicion(x, y);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    // Inicialmente invisible
    //setVisible(false);
    energiaMaxima = 100;
    energia = energiaMaxima;
    vidas = 3;

    barraEnergia = new QGraphicsRectItem(0, 0, 100, 10);
    barraEnergia->setBrush(Qt::green);
    barraEnergia->setZValue(1);
    barraEnergia->setParentItem(this);
    barraEnergia->setPos(10, -15);
}

HombreInvisible::~HombreInvisible() {

}

void HombreInvisible::mover() {
    // Movimiento aleatorio limitado en la plataforma
    if (vx == 0) vx = 0.1;

    // Cambio aleatorio de dirección de vez en cuando
    if (rand() % 30 == 0) {  // Cambia dirección cada ~0.5 segundos (si el timer es 16 ms)
        direccionX = (rand() % 3) - 1; // -1, 0, 1
        direccionY = (rand() % 3) - 1;
    }

    // Actualizar posición según dirección
    x += direccionX * 2 + vx;
    y += direccionY * 2;

    // Limitar al rango de pantalla (ajustar al tamaño real del sprite)
    int anchoSprite = 120;
    int altoSprite = 120;
    x = qBound(0.0f, x, 800.0f - anchoSprite);
    y = qBound(350.0f, y, 600.0f - altoSprite);

    // Aplicar física adicional
    actualizarFisica();
    setPosicion(x, y);

    // Actualizar sprite según dirección X
    if (direccionX > 0)
        setPixmap(frameDerecha.scaled(120, 120));
    else if (direccionX < 0)
        setPixmap(frameIzquierda.scaled(120, 120));
}



void HombreInvisible::actualizarFisica() {
    if (fisica) fisica->aplicarFisica(x, y, vx, vy);
}


void HombreInvisible::activarVisibilidadTemporal(int milisegundos) {
    visible = true;
    // Inicialmente invisible
    setVisible(true);
    temporizadorVisibilidad->start(milisegundos);
}

bool HombreInvisible::estaVisible() const {
    return visible;
}

void HombreInvisible::actualizarBarraEnergia() {
    float porcentaje = static_cast<float>(energia) / energiaMaxima;
    barraEnergia->setRect(0, 0, 100 * porcentaje, 10);

    if (porcentaje > 0.6)
        barraEnergia->setBrush(Qt::green);
    else if (porcentaje > 0.3)
        barraEnergia->setBrush(Qt::yellow);
    else
        barraEnergia->setBrush(Qt::red);
}


void HombreInvisible::recibirDanio() {
    energia -= 20;
    if (energia < 0) energia = 0;
    actualizarBarraEnergia();

    if (energia == 0) {
        vidas--;
        actualizarCorazones();
        if (vidas > 0) {
            energia = energiaMaxima;
            actualizarBarraEnergia();
        } else {
            // Mostrar ventana de victoria
            QMessageBox msgBox;
            msgBox.setWindowTitle("¡Victoria!");
            msgBox.setText("Has derrotado al enemigo.\n¿Deseas salir o pasar al Nivel 2?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Salir");
            msgBox.setButtonText(QMessageBox::No, "Nivel 2");
            int result = msgBox.exec();

            if (result == QMessageBox::Yes) {
                QApplication::quit();
            } else {
                // Aquí iría la lógica para cargar Nivel 2
                qDebug() << "Cargar Nivel 2 (a implementar)";
                vista->scene()->clear();  // Limpia nivel 1
                Nivel2* nivel2 = new Nivel2(vista);
                nivel2->iniciar();
            }
        }
    }
}

void HombreInvisible::inicializarCorazones() {
    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem* corazon = new QGraphicsPixmapItem(QPixmap(":/images/corazon.png").scaled(25, 25));
        corazon->setZValue(2);
        scene()->addItem(corazon);
        corazon->setPos(700 + i * 30, 10);  // parte superior derecha
        corazones.append(corazon);
    }
}

void HombreInvisible::actualizarCorazones() {
    for (int i = 0; i < corazones.size(); ++i) {
        corazones[i]->setVisible(i < vidas);
    }
}

void HombreInvisible::reiniciarEstado() {
    vidas = 3;
    energia = energiaMaxima;
    actualizarBarraEnergia();
    actualizarCorazones();
    setPos(400, 300);
    setVisible(true);
}

