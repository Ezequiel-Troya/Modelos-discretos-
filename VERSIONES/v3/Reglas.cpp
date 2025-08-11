#include "Reglas.h"

std::string aplicarReglas(Jugador& j1, Jugador& j2, int valorA, int valorB, int valorC) {
    std::string resultado;

    auto sumarPuntos = [&](Jugador& j, int puntos) {
        j.puntaje += puntos;
        resultado += j.nombre + " suma " + std::to_string(puntos) + " puntos.\n";
        };

    auto restarPuntos = [&](Jugador& j, int puntos) {
        j.puntaje -= puntos;
        resultado += j.nombre + " pierde " + std::to_string(puntos) + " puntos.\n";
        };

    auto mensajeMal = [&](Jugador& j) {
        resultado += j.nombre + " respondió mal y no suma puntos.\n";
        };

    if (!j1.respuestaCorrecta && !j2.respuestaCorrecta) {
        mensajeMal(j1);
        mensajeMal(j2);
        return resultado;
    }

    if (j1.respuestaCorrecta && !j2.respuestaCorrecta) {
        if (j1.eleccion == j2.eleccion) {
            if (j1.eleccion == 'A') sumarPuntos(j1, valorA);
            else if (j1.eleccion == 'B') sumarPuntos(j1, valorB);
            else sumarPuntos(j1, valorC);
        }
        else if ((j1.eleccion == 'A' && j2.eleccion == 'C')) sumarPuntos(j1, valorB);
        else if ((j1.eleccion == 'C' && j2.eleccion == 'A')) sumarPuntos(j1, valorC - 5);
        else if ((j1.eleccion == 'B' && j2.eleccion == 'C')) sumarPuntos(j1, valorB);
        else if ((j1.eleccion == 'C' && j2.eleccion == 'B')) sumarPuntos(j1, valorC);
        else if ((j1.eleccion == 'A' && j2.eleccion == 'B')) restarPuntos(j1, 20);
        else if ((j1.eleccion == 'B' && j2.eleccion == 'A')) restarPuntos(j1, 10);
        mensajeMal(j2);
        return resultado;
    }

    if (!j1.respuestaCorrecta && j2.respuestaCorrecta) {
        if (j1.eleccion == j2.eleccion) {
            if (j2.eleccion == 'A') sumarPuntos(j2, valorA);
            else if (j2.eleccion == 'B') sumarPuntos(j2, valorB);
            else sumarPuntos(j2, valorC);
        }
        else if ((j2.eleccion == 'A' && j1.eleccion == 'C')) sumarPuntos(j2, valorB);
        else if ((j2.eleccion == 'C' && j1.eleccion == 'A')) sumarPuntos(j2, valorC - 5);
        else if ((j2.eleccion == 'B' && j1.eleccion == 'C')) sumarPuntos(j2, valorB);
        else if ((j2.eleccion == 'C' && j1.eleccion == 'B')) sumarPuntos(j2, valorC);
        else if ((j2.eleccion == 'A' && j1.eleccion == 'B')) restarPuntos(j2, 20);
        else if ((j2.eleccion == 'B' && j1.eleccion == 'A')) restarPuntos(j2, 10);
        mensajeMal(j1);
        return resultado;
    }

    if (j1.respuestaCorrecta && j2.respuestaCorrecta) {
        if (j1.eleccion == j2.eleccion) {
            if (j1.eleccion == 'A') { sumarPuntos(j1, valorA); sumarPuntos(j2, valorA); }
            else if (j1.eleccion == 'B') { sumarPuntos(j1, valorB); sumarPuntos(j2, valorB); }
            else { sumarPuntos(j1, valorC); sumarPuntos(j2, valorC); }
        }
        else if ((j1.eleccion == 'A' && j2.eleccion == 'C') || (j1.eleccion == 'C' && j2.eleccion == 'A')) {
            if (j1.eleccion == 'C') { sumarPuntos(j1, valorC - 5); sumarPuntos(j2, valorB); }
            else { sumarPuntos(j2, valorC - 5); sumarPuntos(j1, valorB); }
        }
        else if ((j1.eleccion == 'B' && j2.eleccion == 'C') || (j1.eleccion == 'C' && j2.eleccion == 'B')) {
            if (j1.eleccion == 'B') { sumarPuntos(j1, valorB); sumarPuntos(j2, valorC); }
            else { sumarPuntos(j2, valorB); sumarPuntos(j1, valorC); }
        }
        else if ((j1.eleccion == 'A' && j2.eleccion == 'B') || (j1.eleccion == 'B' && j2.eleccion == 'A')) {
            if (j1.eleccion == 'B') { restarPuntos(j1, 10); restarPuntos(j2, 20); }
            else { restarPuntos(j2, 10); restarPuntos(j1, 20); }
        }
    }

    return resultado;
}
