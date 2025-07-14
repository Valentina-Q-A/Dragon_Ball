#include "poder.h"
#include "hombreinvisible.h"
#include "qgraphicsscene.h"
#include <QtMath>
#include <QList>
#include "hombreenmascarado.h"
#include "poderenemigo.h"
#include "jugador.h"
#include <stdexcept>



Poder::Poder(QPointF inicio, QPointF destino, float velocidad, QGraphicsScene* escena)
    : velocidad(velocidad), escenaRef(escena) {
    QPixmap sprite(":/images/poder.png");
    if (sprite.isNull()) {
        throw std::runtime_error("No se pudo cargar el sprite del poder");
    }
    setPixmap(sprite.scaled(40, 40));

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
            enemigo->recibirDanio();
            escenaRef->removeItem(this);
            deleteLater();
            return;
        }

        if (HombreEnmascarado* enemigo2 = dynamic_cast<HombreEnmascarado*>(item)) {

            qreal direccion = (x() < enemigo2->pos().x()) ? 20.0 : -20.0;
            enemigo2->moveBy(direccion, 0);
            enemigo2->recibirDanio();

            // Efecto visual de daño
            enemigo2->setOpacity(0.6);
            QTimer::singleShot(150, enemigo2, [enemigo2]() {
                enemigo2->setOpacity(1.0);
            });

            escenaRef->removeItem(this);
            deleteLater();
            return;
        }

        // Empuje energético si choca con poder enemigo
        if (PoderEnemigo* poderEnemigo = dynamic_cast<PoderEnemigo*>(item)) {

            QList<QGraphicsItem*> items = escenaRef->items();
            for (QGraphicsItem* obj : items) {
                if (Jugador* goku = dynamic_cast<Jugador*>(obj)) {
                    goku->moveBy(-20, 0);
                }
                if (HombreEnmascarado* enemigo = dynamic_cast<HombreEnmascarado*>(obj)) {
                    enemigo->moveBy(20, 0);
                }
            }

            // Destruir ambos poderes
            escenaRef->removeItem(poderEnemigo);
            poderEnemigo->deleteLater();

            escenaRef->removeItem(this);
            deleteLater();
            return;
        }

    }

    // eliminar si se sale del mapa
    if (x() < 0 || x() > 800 || y() < 0 || y() > 600) {
        escenaRef->removeItem(this);
        deleteLater();
    }
}
