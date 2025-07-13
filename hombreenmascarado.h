#ifndef HOMBREENMASCARADO_H
#define HOMBREENMASCARADO_H

#include "enemigo.h"
#include <QPixmap>
#include <QTimer>

class HombreEnmascarado : public Enemigo {
    Q_OBJECT

public:
    HombreEnmascarado(float x, float y);
    ~HombreEnmascarado();

    void mover() override;
    void actualizarFisica() override;
    void inicializarCorazones();
    void actualizarCorazones();
    void recibirDanio();
    void reiniciarEstado();

private:
    QPixmap frameDerecha;
    QPixmap frameIzquierda;

    QGraphicsRectItem* barraEnergia;
    QList<QGraphicsPixmapItem*> corazones;

    int energia;
    int energiaMaxima;
    int vidas;

    int direccionX;
    int direccionY;
};

#endif // HOMBREENMASCARADO_H
