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
    bool movimientoActivo;
    void setEnSalto(bool estado);

    enum Direccion { Abajo, Izquierda, Derecha, Arriba };
    Direccion ultimaDireccion;

    void recibirGolpe();  // nuevo método
    void actualizarBarraEnergia();
    void inicializarCorazones();
    void actualizarCorazones();
    void limitarPosicion();
    bool estaEnNivel2 = false;
    Direccion getUltimaDireccion() const { return ultimaDireccion; }
    QRectF areaSegura;

    void setAreaSegura(const QRectF& area) { areaSegura = area; }
    void verificarCaida();




private:
    int vidas;
    int energia;
    int golpesAcertados;
    int energiaMaxima;
    QPointF posicion;
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
    SaltoParabolico* saltoParabolico;
};

#endif // JUGADOR_H

