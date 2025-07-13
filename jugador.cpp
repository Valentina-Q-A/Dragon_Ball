#include "Jugador.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "hombreinvisible.h"

#include "../fisicas/SaltoParabolico.h"

#include "../niveles/nivel1.h"
#include "poder.h"


#include <QMessageBox>
#include <QApplication>

extern Nivel1* nivelGlobal; // Si es global, o buscás la escena de otra forma


Jugador::Jugador(QObject *parent)
    : QObject(parent), vidas(3), energia(100), golpesAcertados(0), enSalto(false), ultimaDireccion(Abajo) {

    QPixmap spriteSheet(":/images/goku.png");

    if (spriteSheet.isNull()) {
        qDebug() << "No se pudo cargar el spriteSheet de Goku";
    }
    // Coordenadas de ejemplo: ajustalas según tu sprite
    frameDerecha   = spriteSheet.copy(  345,  0, 345, 547);
    frameIzquierda = spriteSheet.copy( 345,  547, 345, 547);
    frameArriba   = spriteSheet.copy(  345,  1094, 345, 547);
    frameAbajo   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueDerecha   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueIzquierda   = spriteSheet.copy(  0,  0, 380, 547);
    frameAtaqueAbajo   = spriteSheet.copy(  0,  0, 380, 547);
    frameRecibirDanio = spriteSheet.copy(  0,  0, 380, 547);

    setPixmap(frameDerecha.scaled(120, 120));


    setPos(100, 300);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    // Inicializar física de salto
    //salto = new SaltoParabolico(25.2f, 9.8f, 1.2f);  // v0, g, duración máxima
    salto = new SaltoParabolico(40.0f, 40.0f, 0.5f);  // v0, g, duración

    frameAtaque = QPixmap(":/images/goku_ataque.png"); // ← agregá este sprite a tu proyecto
    timerAtaque = new QTimer(this);
    connect(timerAtaque, &QTimer::timeout, [this]() {
        setPixmap(frameDerecha.scaled(120, 120)); // ← o la última dirección que corresponda
        timerAtaque->stop();
    });

    frameRecibirDanio = QPixmap(":/images/goku_danio.png");  // Sprite ya cargado
    timerDanio = new QTimer(this);
    connect(timerDanio, &QTimer::timeout, [this]() {
        // Restaurar sprite según dirección
        switch (ultimaDireccion) {
        case Derecha:  setPixmap(frameDerecha.scaled(120, 120)); break;
        case Izquierda:setPixmap(frameIzquierda.scaled(120, 120)); break;
        case Abajo:    setPixmap(frameAbajo.scaled(120, 120)); break;
        case Arriba:   setPixmap(frameArriba.scaled(120, 120)); break;
        }
        timerDanio->stop();
    });
    energiaMaxima = 100;
    energia = energiaMaxima;
    vidas = 3;

    barraEnergia = new QGraphicsRectItem(0, 0, 100, 10);
    barraEnergia->setBrush(Qt::green);
    barraEnergia->setZValue(1);
    barraEnergia->setParentItem(this);
    barraEnergia->setPos(0, -15);  // encima del personaje
}

void Jugador::moverIzquierda() {
    setX(x() - 10);
    ultimaDireccion = Izquierda;
    setPixmap(frameIzquierda.scaled(120, 120));
    movimientoActivo = true;
    limitarPosicion();

}

void Jugador::moverDerecha() {
    setX(x() + 10);
    ultimaDireccion = Derecha;
    setPixmap(frameDerecha.scaled(120, 120));
    movimientoActivo = true;
    limitarPosicion();

}

void Jugador::moverArriba() {
    setY(y() - 10);
    ultimaDireccion = Arriba;
    setPixmap(frameArriba.scaled(120, 120));
    movimientoActivo = true;
    limitarPosicion();

}

void Jugador::moverAbajo() {
    setY(y() + 10);
    ultimaDireccion = Abajo;
    setPixmap(frameAbajo.scaled(120, 120));
    movimientoActivo = true;
    limitarPosicion();

}

void Jugador::saltar() {
    movimientoActivo = false;
    if (!enSalto) {
        enSalto = true;
        salto->aplicar(this);  // se libera automáticamente al aterrizar
    }
}

void Jugador::atacar() {
    // 1. Cambiar sprite según dirección
    switch (ultimaDireccion) {
    case Derecha:
        setPixmap(frameAtaqueDerecha.scaled(120, 120));
        break;
    case Izquierda:
        setPixmap(frameAtaqueIzquierda.scaled(120, 120));
        break;
    case Abajo:
        setPixmap(frameAtaqueAbajo.scaled(120, 120));
        break;
    case Arriba:
        setPixmap(frameAtaqueAbajo.scaled(120, 120)); // Reutiliza sprite de abajo
        break;
    }

    // 2. Volver al sprite normal luego de 300 ms
    timerAtaque->start(300);

    // 3. Determinar dirección del ataque
    QPointF origen = this->pos();
    QPointF destino;
    HombreInvisible* objetivo = nullptr;

    QList<QGraphicsItem*> items = scene()->items();
    for (QGraphicsItem* item : items) {
        HombreInvisible* enemigo = dynamic_cast<HombreInvisible*>(item);
        if (enemigo && enemigo->estaVisible()) {
            objetivo = enemigo;
            break;
        }
    }

    if (objetivo) {
        destino = objetivo->pos(); // Apunta al enemigo si está visible
    } else {
        // Si no hay enemigo visible, lanzar en la dirección de Goku
        float offset = 100.0f;  // Distancia fija
        switch (ultimaDireccion) {
        case Derecha:
            destino = QPointF(origen.x() + offset, origen.y());
            break;
        case Izquierda:
            destino = QPointF(origen.x() - offset, origen.y());
            break;
        case Abajo:
            destino = QPointF(origen.x(), origen.y() + offset);
            break;
        case Arriba:
            destino = QPointF(origen.x(), origen.y() - offset);
            break;
        }
    }

    // 4. Lanzar el poder
    Poder* poder = new Poder(origen, destino, 10.0f, scene());
}



void Jugador::recibirDanio(int cantidad) {
    vidas -= cantidad;
    if (vidas < 0) vidas = 0;
}

void Jugador::recibirGolpe() {
    energia -= 20;
    if (energia < 0) energia = 0;

    setPixmap(frameRecibirDanio.scaled(120, 120));

    timerDanio->start(300);
    actualizarBarraEnergia();

    if (energia == 0) {
        vidas--;
        actualizarCorazones();
        if (vidas > 0) {
            // Reiniciar energía
            energia = energiaMaxima;
            actualizarBarraEnergia();
        } else {
            // Mostrar mensaje de fin de juego
            QMessageBox msgBox;
            msgBox.setWindowTitle("¡Game Over!");
            msgBox.setText("Te has quedado sin vidas.\n¿Deseas reiniciar el juego o salir?");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
            int result = msgBox.exec();

            if (result == QMessageBox::Retry) {
                reiniciarEstado();
                actualizarBarraEnergia();
            } else {
                QApplication::quit();
            }
        }
    }
}


void Jugador::reiniciarEstado() {
    vidas = 3;
    energia = energiaMaxima;
    golpesAcertados = 0;
    setPos(100, 300);
    actualizarBarraEnergia();
    actualizarCorazones();

}

void Jugador::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Jugador recibió tecla:" << event->key();  // ← DEBUG CRÍTICO
    //if (event->isAutoRepeat()) return;  // Ignora repeticiones
    switch (event->key()) {
    case Qt::Key_Left:
        moverIzquierda();
        break;
    case Qt::Key_Right:
        moverDerecha();
        break;
    case Qt::Key_Up:
        moverArriba();
        break;
    case Qt::Key_Down:
        moverAbajo();
        break;
    case Qt::Key_Space:
        saltar();
        break;
    case Qt::Key_X:
        atacar();
        break;
    }
}

void Jugador::setEnSalto(bool valor) {
    enSalto = valor;
}



/*float Jugador::getVelocidad() const {
    return velocidad;
}*/

/*void Jugador::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;  // Ignora repeticiones
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        movimientoActivo = false;
        break;
    }
}*/


void Jugador::actualizarBarraEnergia() {
    float porcentaje = static_cast<float>(energia) / energiaMaxima;
    barraEnergia->setRect(0, 0, 100 * porcentaje, 10);

    if (porcentaje > 0.6)
        barraEnergia->setBrush(Qt::green);
    else if (porcentaje > 0.3)
        barraEnergia->setBrush(Qt::yellow);
    else
        barraEnergia->setBrush(Qt::red);
}


void Jugador::inicializarCorazones() {
    if (!scene()) return;
    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem* corazon = new QGraphicsPixmapItem(QPixmap(":/images/corazon.png").scaled(30, 30));
        corazon->setZValue(2);
        corazon->setPos(10 + i * 35, 10);  // separados y ubicados arriba a la izquierda
        scene()->addItem(corazon);
        corazones.append(corazon);
    }
}

void Jugador::actualizarCorazones() {
    for (int i = 0; i < corazones.size(); ++i) {
        corazones[i]->setVisible(i < vidas);
    }
}


void Jugador::limitarPosicion() {
    int anchoSprite = 120;
    int altoSprite = 120;

    float nuevaX = qBound(0.0f, x(), 800.0f - anchoSprite);
    float nuevaY = qBound(350.0f, y(), 600.0f - altoSprite);

    setPos(nuevaX, nuevaY);
}
