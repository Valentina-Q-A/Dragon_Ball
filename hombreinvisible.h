#ifndef HOMBREINVISIBLE_H
#define HOMBREINVISIBLE_H

#include "enemigo.h"
#include <QTimer>
#include <QPainter>
#include <QObject>

class HombreInvisible : public QObject, public Enemigo {
    Q_OBJECT

private:
    bool visible;
    QTimer* temporizadorVisibilidad;

public:
    HombreInvisible(float x, float y);
    ~HombreInvisible();

    void mover() override;
    void actualizarFisica() override;
    void dibujar(QPainter* painter) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void activarVisibilidadTemporal(int milisegundos);
    bool estaVisible() const;
};

#endif // HOMBREINVISIBLE_H

