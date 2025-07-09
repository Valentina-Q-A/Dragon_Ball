#include "movimientooscilatorio.h"
#include <cmath>

MovimientoOscilatorio::MovimientoOscilatorio(float xBase, float amplitud, float frecuencia)
    : Fisica("MovimientoOscilatorio", 0), xBase(xBase), amplitud(amplitud), frecuencia(frecuencia), tiempo(0.01) {}

void MovimientoOscilatorio::aplicarFisica(float& x, float& y, float& vx, float& vy) {
    tiempo += 0.016f; // Simulando 60 FPS
    //x = xBase + amplitud * sin(2 * M_PI * frecuencia * tiempo);
    vx = 2 * M_PI * frecuencia * amplitud * cos(2 * M_PI * frecuencia * tiempo);
}
