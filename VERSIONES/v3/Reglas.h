#ifndef REGLAS_H
#define REGLAS_H

#include <string>

struct Jugador {
    int puntaje = 0;
    char eleccion = 0; // 'A', 'B' o 'C'
    bool respuestaCorrecta = false;
    std::string nombre;
};

// Aplica las reglas y modifica puntajes, devuelve mensajes para mostrar en SFML
std::string aplicarReglas(Jugador& j1, Jugador& j2, int valorA, int valorB, int valorC);

#endif // REGLAS_H
