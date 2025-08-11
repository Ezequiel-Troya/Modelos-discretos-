#include "Preguntas.h"
#include <fstream>
#include <cctype>

bool GestorPreguntas::cargarPreguntas(const std::string& archivo) {
    preguntas.clear();
    indiceActual = 0;

    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    std::string linea;
    while (std::getline(file, linea)) {
        // Saltar líneas vacías o comentarios
        while ((linea.empty() || linea[0] == '#') && std::getline(file, linea));
        if (file.eof() || linea.empty() || linea[0] == '#') break;

        Pregunta p;
        p.enunciado = linea;

        bool completa = true;
        for (int i = 0; i < 3; ++i) {
            while (std::getline(file, linea) && (linea.empty() || linea[0] == '#'));
            if (file.eof() || linea.empty() || linea[0] == '#') { completa = false; break; }
            p.opciones[i] = linea;
        }
        if (!completa) break;

        while (std::getline(file, linea) && (linea.empty() || linea[0] == '#'));
        if (file.eof() || linea.empty() || linea[0] == '#') break;

        p.respuestaCorrecta = std::toupper(linea[0]);
        preguntas.push_back(p);
    }

    return !preguntas.empty();
}

const Pregunta* GestorPreguntas::obtenerPreguntaActual() const {
    if (indiceActual < preguntas.size())
        return &preguntas[indiceActual];
    return nullptr;
}

const Pregunta* GestorPreguntas::obtenerPreguntaPorIndice(size_t i) const {
    if (i >= preguntas.size()) return nullptr;
    return &preguntas[i];
}

void GestorPreguntas::siguientePregunta() {
    if (indiceActual < preguntas.size())
        ++indiceActual;
}

bool GestorPreguntas::validarRespuesta(char respuestaJugador) const {
    if (indiceActual >= preguntas.size()) return false;
    return std::toupper(respuestaJugador) == preguntas[indiceActual].respuestaCorrecta;
}

bool GestorPreguntas::validarRespuesta(char respuestaJugador, size_t i) const {
    if (i >= preguntas.size()) return false;
    return std::toupper(respuestaJugador) == preguntas[i].respuestaCorrecta;
}

void GestorPreguntas::reiniciar() {
    indiceActual = 0;
}

size_t GestorPreguntas::totalPreguntas() const {
    return preguntas.size();
}
