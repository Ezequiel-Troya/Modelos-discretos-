#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>  // para std::ostringstream

struct Seleccion;

class ArbolDecisiones {
private:
    sf::RenderWindow ventana;
    sf::Font fuente;

    std::vector<sf::Text> nodos;
    std::vector<sf::VertexArray> aristas;

    // Textos para mostrar puntuaciones
    sf::Text textoPuntajeJ1;
    sf::Text textoPuntajeJ2;

    void agregarNodos(const std::vector<Seleccion>& decisiones, int yBase, const std::string& jugador);

public:
    ArbolDecisiones();
    void mostrar(const std::vector<Seleccion>& decisionesJugador1, const std::vector<Seleccion>& decisionesJugador2,
        int puntajeJ1 = 0, int puntajeJ2 = 0, const std::string& mensajeResultados = "");
};
