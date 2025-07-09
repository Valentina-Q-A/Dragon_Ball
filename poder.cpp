#include "poder.h"
#include "hombreinvisible.h"
#include "qgraphicsscene.h"
#include <QtMath>
#include <QList>

Poder::Poder(QPointF inicio, QPointF destino, float velocidad, QGraphicsScene* escena)
    : velocidad(velocidad), escenaRef(escena) {

    setPixmap(QPixmap(":/images/poder.png").scaled(40, 40)); // Cargá tu sprite real
    setPos(inicio);
    escena->addItem(this);

    // Calcular dirección normalizada
    float dx = destino.x() - inicio.x();
    float dy = destino.y() - inicio.y();
    float magnitud = qSqrt(dx*dx + dy*dy);
    direccion = QPointF(dx / magnitud, dy / magnitud);

    // Timer de movimiento
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Poder::mover);
    timer->start(16);
}

void Poder::mover() {
    // Mover en la dirección
    moveBy(direccion.x() * velocidad, direccion.y() * velocidad);

    // Verificar colisión con HombreInvisible
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem* item : colisiones) {
        HombreInvisible* enemigo = dynamic_cast<HombreInvisible*>(item);
        if (enemigo && enemigo->estaVisible()) {
            enemigo->setVisible(false);
            escenaRef->removeItem(this);
            deleteLater();
            return;
        }
    }

    // Opcional: eliminar si se sale del mapa
    if (x() < 0 || x() > 800 || y() < 0 || y() > 600) {
        escenaRef->removeItem(this);
        deleteLater();
    }
}
