#ifndef HOMBREINVISIBLE_H
#define HOMBREINVISIBLE_H

#include "enemigo.h"
#include <QTimer>
#include <QObject>
#include <QPixmap>
#include <QGraphicsView>

class Nivel2;  // Adelanto de declaración

class HombreInvisible : public Enemigo {
    Q_OBJECT

private:
    bool visible;
    QTimer* temporizadorVisibilidad;
    QPixmap frameDerecha;
    QPixmap frameIzquierda;

    //Atributos movimiento libre
    int direccionX;
    int direccionY;
    QGraphicsRectItem* barraEnergia;
    int energia;
    int energiaMaxima;
    int vidas;
    QList<QGraphicsPixmapItem*> corazones;
    QGraphicsView* vista;




public:
    HombreInvisible(float x, float y, QGraphicsView* vista);
    ~HombreInvisible();

    void mover() override;
    void actualizarFisica() override;
    void activarVisibilidadTemporal(int milisegundos);
    bool estaVisible() const;
    void actualizarBarraEnergia();
    void recibirDanio();
    void reiniciarEstado();
    void inicializarCorazones();
    void actualizarCorazones();
};

#endif // HOMBREINVISIBLE_H

