#include "GestorPreguntas.h"
#include <fstream>
#include <iostream>

void GestorPreguntas::cargarPreguntas(const std::string& archivo) {
    preguntas.clear();

    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << "\n";
        return;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;

        Pregunta p;
        p.enunciado = linea;

        for (int i = 0; i < 3; i++) {
            if (!std::getline(file, linea)) break;
            p.opciones[i] = linea;
        }

        if (!std::getline(file, linea)) break;

        if (!linea.empty())
            p.respuestaCorrecta = linea[0];
        else
            p.respuestaCorrecta = ' ';

        preguntas.push_back(p);
    }
}

const Pregunta* GestorPreguntas::obtenerPreguntaPorIndice(int i) const {
    if (i < 0 || i >= (int)preguntas.size()) return nullptr;
    return &preguntas[i];
}

int GestorPreguntas::totalPreguntas() const {
    return (int)preguntas.size();
}

bool GestorPreguntas::validarRespuesta(char opcion, int i) const {
    if (i < 0 || i >= (int)preguntas.size()) return false;
    return toupper(opcion) == toupper(preguntas[i].respuestaCorrecta);
}
