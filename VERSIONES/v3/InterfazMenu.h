#ifndef INTERFAZMENU_H
#define INTERFAZMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class InterfazMenu {
public:
    InterfazMenu();
    void ejecutar();
    std::string getDificultadSeleccionada() const;  // Nuevo método para obtener la dificultad

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<std::string> opciones;
    std::vector<sf::Text> textos;
    sf::Color backgroundColor;
    sf::Color colorNormal;
    sf::Color colorSeleccion;
    sf::Text hint;
    int seleccionado;
    bool running;

    void inicializar();
    void procesarEventos();
    void dibujar();
};

#endif // INTERFAZMENU_H