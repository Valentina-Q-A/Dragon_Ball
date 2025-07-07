#include "hombreinvisible.h"
#include "../fisicas/movimientooscilatorio.h"

#include <QGraphicsScene>

HombreInvisible::HombreInvisible(float x, float y)
    : Enemigo(x, y, new MovimientoOscilatorio(x, 50, 0.05)), visible(false) {

    temporizadorVisibilidad = new QTimer(this);
    connect(temporizadorVisibilidad, &QTimer::timeout, [this]() {
        visible = false;
        update(); // Redibuja el sprite
    });

    setPosicion(x, y);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

HombreInvisible::~HombreInvisible() {

}

void HombreInvisible::mover() {
    x += vx;
    actualizarFisica();
    setPosicion(x, y);
}

void HombreInvisible::actualizarFisica() {
    if (fisica) fisica->aplicarFisica(x, y, vx, vy);
}

void HombreInvisible::dibujar(QPainter* painter) {
    if (visible) {
        painter->setBrush(Qt::red);
        painter->drawEllipse(-10, -10, 20, 20); // Sprite visible
    }
    // Si no es visible, no dibuja nada (queda "invisible")
}

QRectF HombreInvisible::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void HombreInvisible::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    dibujar(painter);
}

void HombreInvisible::activarVisibilidadTemporal(int milisegundos) {
    visible = true;
    update();
    temporizadorVisibilidad->start(milisegundos);
}

bool HombreInvisible::estaVisible() const {
    return visible;
}
