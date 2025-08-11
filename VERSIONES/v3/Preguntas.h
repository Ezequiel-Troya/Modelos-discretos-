#ifndef PREGUNTAS_H
#define PREGUNTAS_H

#include <string>
#include <vector>

struct Pregunta {
    std::string enunciado;
    std::string opciones[3];
    char respuestaCorrecta; // 'A', 'B' o 'C'
};

class GestorPreguntas {
private:
    std::vector<Pregunta> preguntas;
    size_t indiceActual = 0;

public:
    // Cargar preguntas desde archivo
    bool cargarPreguntas(const std::string& archivo);

    // Obtener la pregunta actual (según indiceActual)
    const Pregunta* obtenerPreguntaActual() const;

    // Obtener pregunta por índice arbitrario (nuevo)
    const Pregunta* obtenerPreguntaPorIndice(size_t i) const;

    // Pasar a la siguiente pregunta (avanza indiceActual)
    void siguientePregunta();

    // Validar la respuesta (según indiceActual)
    bool validarRespuesta(char respuestaJugador) const;

    // Validar la respuesta para índice arbitrario (nuevo)
    bool validarRespuesta(char respuestaJugador, size_t i) const;

    // Reiniciar el índice de preguntas (por si quieres volver a empezar)
    void reiniciar();

    // Obtener el total de preguntas cargadas (nuevo)
    size_t totalPreguntas() const;
};

#endif

