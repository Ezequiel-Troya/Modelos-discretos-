#include "ArbolDecisiones.h"
#include "InterfazJuego.h"
#include <iostream>
#include <sstream>

ArbolDecisiones::ArbolDecisiones()
    : ventana(sf::VideoMode(1000, 600), "Árbol de Decisiones") {
    if (!fuente.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf\n";
    }

    textoPuntajeJ1.setFont(fuente);
    textoPuntajeJ1.setCharacterSize(24);
    textoPuntajeJ1.setFillColor(sf::Color::Cyan);
    textoPuntajeJ1.setPosition(50, 10);

    textoPuntajeJ2.setFont(fuente);
    textoPuntajeJ2.setCharacterSize(24);
    textoPuntajeJ2.setFillColor(sf::Color::Magenta);
    textoPuntajeJ2.setPosition(550, 10);
}

void ArbolDecisiones::agregarNodos(const std::vector<Seleccion>& decisiones, int yBase, const std::string& jugador) {
    for (size_t i = 0; i < decisiones.size(); ++i) {
        sf::Text nodo;
        nodo.setFont(fuente);
        nodo.setCharacterSize(20);
        nodo.setString(jugador + ": " + decisiones[i].opcion);
        nodo.setPosition(150 + i * 150, yBase);
        nodos.push_back(nodo);

        if (i > 0) {
            sf::VertexArray linea(sf::Lines, 2);
            linea[0].position = sf::Vector2f(150 + (i - 1) * 150 + 40, yBase + 10);
            linea[1].position = sf::Vector2f(150 + i * 150 + 40, yBase + 10);
            linea[0].color = sf::Color::White;
            linea[1].color = sf::Color::White;
            aristas.push_back(linea);
        }
    }
}

void ArbolDecisiones::mostrar(const std::vector<Seleccion>& decisionesJugador1, const std::vector<Seleccion>& decisionesJugador2,
    int puntajeJ1, int puntajeJ2, const std::string& mensajeResultados) {
    nodos.clear();
    aristas.clear();

    agregarNodos(decisionesJugador1, 200, "J1");
    agregarNodos(decisionesJugador2, 350, "J2");

    // Mostrar puntajes
    std::ostringstream ssJ1;
    ssJ1 << "Jugador 1 puntaje final: " << puntajeJ1;
    textoPuntajeJ1.setString(ssJ1.str());

    std::ostringstream ssJ2;
    ssJ2 << "Jugador 2 puntaje final: " << puntajeJ2;
    textoPuntajeJ2.setString(ssJ2.str());

    // Texto de resultados (opcional)
    sf::Text textoResultados;
    textoResultados.setFont(fuente);
    textoResultados.setCharacterSize(20);
    textoResultados.setFillColor(sf::Color::Yellow);
    textoResultados.setPosition(50, 500);
    textoResultados.setString(mensajeResultados);

    while (ventana.isOpen()) {
        sf::Event e;
        while (ventana.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                ventana.close();
        }

        ventana.clear();
        for (auto& nodo : nodos)
            ventana.draw(nodo);
        for (auto& arista : aristas)
            ventana.draw(arista);

        ventana.draw(textoPuntajeJ1);
        ventana.draw(textoPuntajeJ2);
        ventana.draw(textoResultados);

        ventana.display();
    }
}
