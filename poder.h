#ifndef PODER_H
#define PODER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class HombreInvisible;

class Poder : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Poder(QPointF inicio, QPointF destino, float velocidad, QGraphicsScene* escena);

private slots:
    void mover();

private:
    QTimer* timer;
    QPointF direccion;
    float velocidad;
    QGraphicsScene* escenaRef;
};

#endif // PODER_H
