#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Jugador(QObject *parent = nullptr);

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void atacar();
    void recibirDanio(int cantidad);
    void reiniciarEstado();

private:
    int vidas;
    int energia;
    int golpesAcertados;
    QPointF posicion;
    float velocidad;
    bool enSalto;
    QPixmap frameArriba;
    QPixmap frameAbajo;
    QPixmap frameIzquierda;
    QPixmap frameDerecha;

};

#endif // JUGADOR_H
