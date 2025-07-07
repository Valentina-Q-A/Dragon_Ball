#ifndef SALTOPARABOLICO_H
#define SALTOPARABOLICO_H

#include "fisica.h"
#include <QTimer>
#include <QObject>

class SaltoParabolico : public QObject, public Fisica {
    Q_OBJECT

public:
    SaltoParabolico(float velocidadInicial, float gravedad, float duracionMaxima);

    void aplicar(Jugador* j) override;
    void aplicar(Enemigo* e) override {}
    void aplicarFisica(float& x, float& y, float& vx, float& vy) override {} // No se usa aquí

private slots:
    void actualizarSalto();

private:
    Jugador* jugador;
    QTimer* timer;
    float tiempo;
    float y0;
    float v0;
    float g;
    float duracionMaxima;
    float direccionX;
    float vX;
};

#endif // SALTOPARABOLICO_H
