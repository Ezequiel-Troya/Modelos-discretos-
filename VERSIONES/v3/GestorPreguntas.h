#pragma once
#include <vector>
#include <string>

struct Pregunta {
    std::string enunciado;
    std::string opciones[3];
    char respuestaCorrecta;
};

class GestorPreguntas {
private:
    std::vector<Pregunta> preguntas;
public:
    void cargarPreguntas(const std::string& archivo);
    const Pregunta* obtenerPreguntaPorIndice(int i) const;
    int totalPreguntas() const;
    bool validarRespuesta(char opcion, int i) const;
};

