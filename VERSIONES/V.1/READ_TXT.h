#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pregunta {
    string enunciado;
    string opcionA;
    string opcionB;
    string opcionC;
    char respuestaCorrecta;
};

// Función para leer preguntas desde un archivo y devolverlas como vector
vector<Pregunta> cargarPreguntasDesdeArchivo(const string& nombreArchivo) {
    vector<Pregunta> preguntas;
    ifstream archivo(nombreArchivo);
    
    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return preguntas;
    }

    string linea;
    Pregunta temp;
    int paso = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        switch (paso) {
            case 0: temp.enunciado = linea; break;
            case 1: temp.opcionA = linea; break;
            case 2: temp.opcionB = linea; break;
            case 3: temp.opcionC = linea; break;
            case 4: 
                temp.respuestaCorrecta = linea[0]; 
                preguntas.push_back(temp);
                break;
        }
        paso = (paso + 1) % 5;
    }

    archivo.close();
    return preguntas;
}

// Función para mostrar todas las preguntas cargadas
void mostrarPreguntas(const vector<Pregunta>& preguntas) {
    for (size_t i = 0; i < preguntas.size(); ++i) {
        cout << "Pregunta " << i + 1 << ":\n";
        cout << preguntas[i].enunciado << "\n";
        cout << preguntas[i].opcionA << "\n";
        cout << preguntas[i].opcionB << "\n";
        cout << preguntas[i].opcionC << "\n";
        cout << "Respuesta correcta: " << preguntas[i].respuestaCorrecta << "\n\n";
    }
}
