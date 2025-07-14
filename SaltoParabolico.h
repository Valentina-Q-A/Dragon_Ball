#ifndef SALTOPARABOLICO_H
#define SALTOPARABOLICO_H

#include "fisica.h"
#include <QTimer>
#include <QObject>
#include <QVector2D>

class Jugador;

class SaltoParabolico : public QObject, public Fisica {
    Q_OBJECT

public:
    SaltoParabolico(float velocidadInicial, float gravedad, float duracionMaxima);

    void aplicar(Jugador* j) override;
    void aplicar(Enemigo* e) override {}
    void aplicarFisica(float& x, float& y, float& vx, float& vy) override {}

private slots:
    void actualizarSalto();

private:
    Jugador* jugador;          // Referencia al jugador que salta
    QTimer* timer;             // Temporizador para el salto
    float tiempo;              // Tiempo transcurrido
    float dt;                  // Paso de integración
    float y0;                  // Altura inicial (para saber cuándo aterriza)
    float duracionMaxima;      // Tiempo máximo del salto
    float gravedad;
    QVector2D posicion;        // Posición actual
    QVector2D velocidad;       // Velocidad actual
    QVector2D aceleracion;     // Aceleración constante (gravedad)
};

#endif // SALTOPARABOLICO_H
