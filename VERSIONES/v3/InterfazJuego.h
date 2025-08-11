#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Preguntas.h"   

struct Seleccion {
    char opcion;            // 'A', 'B' o 'C'
    int turno;              // 1 o 2
    bool respuestaCorrecta; // NUEVO: si la respuesta fue correcta o no
};


enum EstadoJuego {
    ESPERANDO_SELECCION,  // jugador elige camino
    MOSTRANDO_PREGUNTA,   // muestra pregunta y espera respuesta
    MOSTRANDO_RESULTADO   // muestra si fue correcto o no (pausa corta)
};

struct Jugador {
    int puntaje = 0;
    char eleccion = 0; // 'A','B','C'
    bool respuestaCorrecta = false;
    std::string nombre;
};

class InterfazJuego {
private:
    std::string archivoPreguntas;
    std::vector<Seleccion> decisionesJugador1;
    std::vector<Seleccion> decisionesJugador2;
    int jugadorActual;      // 0 o 1 para jugadores
    int seleccionActual;

    sf::RenderWindow ventana;
    sf::CircleShape puntoCentral;
    sf::Font fuente;

    // Caminos jugador 1
    sf::RectangleShape caminoA, caminoB, caminoC;
    sf::Text textoA, textoB, textoC;

    // Caminos jugador 2
    sf::RectangleShape caminoA2, caminoB2, caminoC2;

    // NUEVO: manejo preguntas y estados
    GestorPreguntas gestorPreguntas;

    EstadoJuego estadoJuego = ESPERANDO_SELECCION;

    // Texto para pregunta, opciones y resultado
    sf::Text textoPregunta;
    sf::Text textoOpciones[3];
    sf::Text textoResultado;

    // Jugadores
    Jugador jugadores[2];

    // Para temporizar pausa tras resultado
    sf::Clock relojPausa;

    // Respuesta del jugador en curso
    char respuestaJugadorActual = 0;

    // NUEVAS VARIABLES PARA ORDEN INVERSO DE PREGUNTAS
    bool ordenInverso = false;  // Si true, preguntas van en orden inverso (jugador 2)
    int indicePregunta = 0;      // Índice actual de la pregunta según el orden

private:
    void mostrarPregunta();
    void manejarRespuesta(char tecla);
    void dibujarEstado();
    void cambiarTurno();

public:
    InterfazJuego(const std::string& dificultad);
    void iniciar();
    void dibujarOpciones();
    void manejarEvento(const sf::Event& evento);
};
