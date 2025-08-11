#include "InterfazJuego.h"
#include "ArbolDecisiones.h"
#include "Reglas.h"
#include <iostream>
#include <cctype>
#include <sstream>

InterfazJuego::InterfazJuego(const std::string& dificultad)
    : jugadorActual(0), seleccionActual(0), ventana(sf::VideoMode(1000, 600), "Juego de Selección"),
    ordenInverso(false), indicePregunta(0) {

    if (dificultad == "facil") archivoPreguntas = "preguntas_facil.txt";
    else if (dificultad == "media") archivoPreguntas = "preguntas_media.txt";
    else archivoPreguntas = "preguntas_dificil.txt";

    puntoCentral.setRadius(20);
    puntoCentral.setFillColor(sf::Color::Red);
    puntoCentral.setPosition(100, 290);

    if (!fuente.loadFromFile("arial.ttf")) {
        std::cerr << "Error cargando fuente arial.ttf\n";
    }

    jugadores[0].nombre = "Jugador 1";
    jugadores[1].nombre = "Jugador 2";

    jugadores[0].puntaje = 0;
    jugadores[1].puntaje = 0;

    // Caminos jugador 1
    caminoA.setSize(sf::Vector2f(200, 80));
    caminoA.setFillColor(sf::Color::Blue);
    caminoA.setPosition(300, 100);

    caminoB.setSize(sf::Vector2f(200, 80));
    caminoB.setFillColor(sf::Color::Green);
    caminoB.setPosition(300, 250);

    caminoC.setSize(sf::Vector2f(200, 80));
    caminoC.setFillColor(sf::Color::Yellow);
    caminoC.setPosition(300, 400);

    textoA.setFont(fuente);
    textoA.setString("A");
    textoA.setCharacterSize(30);
    textoA.setPosition(370, 120);

    textoB.setFont(fuente);
    textoB.setString("B");
    textoB.setCharacterSize(30);
    textoB.setPosition(370, 270);

    textoC.setFont(fuente);
    textoC.setString("C");
    textoC.setCharacterSize(30);
    textoC.setPosition(370, 420);

    // Caminos jugador 2
    caminoA2.setSize(sf::Vector2f(200, 80));
    caminoA2.setFillColor(sf::Color::Blue);
    caminoA2.setPosition(500, 100);

    caminoB2.setSize(sf::Vector2f(200, 80));
    caminoB2.setFillColor(sf::Color::Green);
    caminoB2.setPosition(500, 250);

    caminoC2.setSize(sf::Vector2f(200, 80));
    caminoC2.setFillColor(sf::Color::Yellow);
    caminoC2.setPosition(500, 400);

    gestorPreguntas.cargarPreguntas(archivoPreguntas);

    estadoJuego = ESPERANDO_SELECCION;

    textoPregunta.setFont(fuente);
    textoPregunta.setCharacterSize(24);
    textoPregunta.setFillColor(sf::Color::White);
    textoPregunta.setPosition(50, 50);

    for (int i = 0; i < 3; i++) {
        textoOpciones[i].setFont(fuente);
        textoOpciones[i].setCharacterSize(20);
        textoOpciones[i].setFillColor(sf::Color::White);
        textoOpciones[i].setPosition(80, 120 + i * 40);
    }

    textoResultado.setFont(fuente);
    textoResultado.setCharacterSize(22);
    textoResultado.setFillColor(sf::Color::Yellow);
    textoResultado.setPosition(50, 280);

    ordenInverso = false;
    indicePregunta = 0;
}

void InterfazJuego::iniciar() {
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            else if (estadoJuego == ESPERANDO_SELECCION && evento.type == sf::Event::MouseButtonPressed) {
                manejarEvento(evento);
            }
            else if (estadoJuego == MOSTRANDO_PREGUNTA && evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::A) manejarRespuesta('A');
                else if (evento.key.code == sf::Keyboard::B) manejarRespuesta('B');
                else if (evento.key.code == sf::Keyboard::C) manejarRespuesta('C');
            }
        }

        if (estadoJuego == MOSTRANDO_RESULTADO) {
            if (relojPausa.getElapsedTime().asSeconds() >= 2) {
                Seleccion sel = { jugadores[jugadorActual].eleccion, jugadorActual + 1 };
                if (jugadorActual == 0) decisionesJugador1.push_back(sel);
                else decisionesJugador2.push_back(sel);

                seleccionActual++;

                if (seleccionActual >= 5 && jugadorActual == 0) {
                    jugadorActual = 1;
                    seleccionActual = 0;
                    puntoCentral.setFillColor(sf::Color::White);

                    ordenInverso = true;
                    indicePregunta = gestorPreguntas.totalPreguntas() - 1;
                }
                else if (seleccionActual >= 5 && jugadorActual == 1) {
                    ventana.close();

                    std::string mensajesReglas;
                    for (size_t i = 0; i < decisionesJugador1.size(); ++i) {
                        mensajesReglas += aplicarReglas(
                            jugadores[0],
                            jugadores[1],
                            10, // valorA
                            15, // valorB
                            20  // valorC
                        );
                    }

                    std::ostringstream resumen;
                    resumen << mensajesReglas
                        << "Puntaje final " << jugadores[0].nombre << ": " << jugadores[0].puntaje << "\n"
                        << "Puntaje final " << jugadores[1].nombre << ": " << jugadores[1].puntaje;

                    ArbolDecisiones arbol;
                    arbol.mostrar(decisionesJugador1, decisionesJugador2,
                        jugadores[0].puntaje, jugadores[1].puntaje,
                        resumen.str());
                }
                estadoJuego = ESPERANDO_SELECCION;
                puntoCentral.setPosition(100, 290);
            }
        }

        dibujarEstado();
    }
}

void InterfazJuego::mostrarPregunta() {
    const Pregunta* p = gestorPreguntas.obtenerPreguntaPorIndice(indicePregunta);
    if (!p) return;

    textoPregunta.setString(p->enunciado);
    for (int i = 0; i < 3; i++) {
        textoOpciones[i].setString(p->opciones[i]);
    }
    textoResultado.setString("");
}

void InterfazJuego::manejarRespuesta(char tecla) {
    tecla = toupper(tecla);

    if (tecla != 'A' && tecla != 'B' && tecla != 'C') return;

    respuestaJugadorActual = tecla;
    jugadores[jugadorActual].eleccion = tecla;

    bool correcta = gestorPreguntas.validarRespuesta(tecla, indicePregunta);
    jugadores[jugadorActual].respuestaCorrecta = correcta;

    if (correcta)
        textoResultado.setString("¡Correcto!");
    else {
        const Pregunta* p = gestorPreguntas.obtenerPreguntaPorIndice(indicePregunta);
        textoResultado.setString("Incorrecto. Respuesta correcta: " + std::string(1, p->respuestaCorrecta));
    }

    estadoJuego = MOSTRANDO_RESULTADO;
    relojPausa.restart();

    if (!ordenInverso) indicePregunta++;
    else indicePregunta--;
}

void InterfazJuego::dibujarOpciones() {
    if (jugadorActual == 0) {
        ventana.draw(caminoA);
        ventana.draw(caminoB);
        ventana.draw(caminoC);
        ventana.draw(textoA);
        ventana.draw(textoB);
        ventana.draw(textoC);
    }
    else {
        ventana.draw(caminoA2);
        ventana.draw(caminoB2);
        ventana.draw(caminoC2);

        sf::Text textoA2("A", fuente, 30);
        sf::Text textoB2("B", fuente, 30);
        sf::Text textoC2("C", fuente, 30);
        textoA2.setPosition(570, 120);
        textoB2.setPosition(570, 270);
        textoC2.setPosition(570, 420);
        ventana.draw(textoA2);
        ventana.draw(textoB2);
        ventana.draw(textoC2);
    }
}

void InterfazJuego::dibujarEstado() {
    ventana.clear();

    if (estadoJuego == ESPERANDO_SELECCION) {
        dibujarOpciones();
        ventana.draw(puntoCentral);
    }
    else if (estadoJuego == MOSTRANDO_PREGUNTA || estadoJuego == MOSTRANDO_RESULTADO) {
        ventana.draw(textoPregunta);
        for (int i = 0; i < 3; i++) ventana.draw(textoOpciones[i]);
        if (estadoJuego == MOSTRANDO_RESULTADO) ventana.draw(textoResultado);
    }

    ventana.display();
}

void InterfazJuego::manejarEvento(const sf::Event& evento) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);

    if (estadoJuego != ESPERANDO_SELECCION) return;

    auto moverJugador = [&](float yDestino, char opcion, sf::Color color) {
        puntoCentral.setFillColor(color);
        puntoCentral.setPosition((jugadorActual == 0) ? 300 : 500, yDestino);
        ventana.clear();
        dibujarOpciones();
        ventana.draw(puntoCentral);
        ventana.display();

        jugadores[jugadorActual].eleccion = opcion;
        mostrarPregunta();
        estadoJuego = MOSTRANDO_PREGUNTA;
        };

    if (jugadorActual == 0) {
        if (caminoA.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(120, 'A', sf::Color::Red);
        else if (caminoB.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(270, 'B', sf::Color::Red);
        else if (caminoC.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(420, 'C', sf::Color::Red);
    }
    else {
        if (caminoA2.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(120, 'A', sf::Color::White);
        else if (caminoB2.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(270, 'B', sf::Color::White);
        else if (caminoC2.getGlobalBounds().contains(mousePos.x, mousePos.y)) moverJugador(420, 'C', sf::Color::White);
    }
}
