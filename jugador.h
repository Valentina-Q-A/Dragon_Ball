#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QPixmap>
#include "../fisicas/SaltoParabolico.h"


class SaltoParabolico;

class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

    explicit Jugador(QObject *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void saltar();
    void atacar();
    void recibirDanio(int cantidad);
    void reiniciarEstado();
    //ESTABA BIEN SIN FISICAS
    bool movimientoActivo;
    void setEnSalto(bool estado);
    //float getVelocidad() const;

    enum Direccion { Abajo, Izquierda, Derecha, Arriba };
    Direccion ultimaDireccion;

    void recibirGolpe();  // nuevo método
    void actualizarBarraEnergia();
    void inicializarCorazones();
    void actualizarCorazones();
    void limitarPosicion();

    //void keyReleaseEvent(QKeyEvent *event);



private:
    int vidas;
    int energia;
    int golpesAcertados;
    int energiaMaxima;
    QPointF posicion;
    //float velocidad;
    bool enSalto;
    // Sprites
    QPixmap frameArriba;
    QPixmap frameAbajo;
    QPixmap frameIzquierda;
    QPixmap frameDerecha;
    QPixmap frameAtaqueDerecha;
    QPixmap frameAtaqueIzquierda;
    QPixmap frameAtaqueAbajo;
    QPixmap frameRecibirDanio;
    QPixmap frameAtaque;

    QTimer* timerAtaque;
    QTimer* timerDanio;
    SaltoParabolico *salto;
    QGraphicsRectItem* barraEnergia;
    QList<QGraphicsPixmapItem*> corazones;
};

#endif // JUGADOR_H

