#ifndef HOMBREINVISIBLE_H
#define HOMBREINVISIBLE_H

#include "enemigo.h"
#include <QTimer>
#include <QObject>
#include <QPixmap>

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


public:
    HombreInvisible(float x, float y);
    ~HombreInvisible();

    void mover() override;
    void actualizarFisica() override;
    void activarVisibilidadTemporal(int milisegundos);
    bool estaVisible() const;
};

#endif // HOMBREINVISIBLE_H

