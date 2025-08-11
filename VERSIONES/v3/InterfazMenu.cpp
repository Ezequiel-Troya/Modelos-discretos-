#include "InterfazMenu.h"
#include <iostream>

InterfazMenu::InterfazMenu()
    : window(sf::VideoMode(800, 600), "Camino de Eleccion - Menu", sf::Style::Close),
    backgroundColor(173, 216, 230), // light blue
    colorNormal(sf::Color::White),
    colorSeleccion(sf::Color(255, 215, 0)), // gold
    seleccionado(0),
    running(true) {
    inicializar();
}

void InterfazMenu::inicializar() {
    window.setFramerateLimit(60);

    // Cargar fuente Arial desde la ubicación específica
    if (!font.loadFromFile("C:\\Users\\Asus\\source\\repos\\SFML_GAME\\arial.ttf")) {
        std::cerr << "Error: no se pudo cargar la fuente C:\\Users\\Asus\\source\\repos\\SFML_GAME\\arial.ttf\n";
        std::cerr << "Verifica que el archivo arial.ttf esté en C:\\Users\\Asus\\source\\repos\\SFML_GAME\\\n";
        running = false; // Detener ejecución si falla la fuente
    }

    // Titulo
    title.setFont(font);
    title.setString("CAMINO DE ELECCION");
    title.setCharacterSize(48);
    title.setPosition(800.f / 2 - title.getGlobalBounds().width / 2, 60.f);

    // Opciones de dificultad
    opciones = { "FACIL", "INTERMEDIO", "DIFICIL" };
    const float startY = 220.f;
    const float gapY = 70.f;

    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text t(opciones[i], font, 32);
        t.setPosition(800.f / 2 - t.getGlobalBounds().width / 2, startY + i * gapY);
        textos.push_back(t);
    }
    textos[seleccionado].setFillColor(colorSeleccion);

    // Texto indicador
    hint.setFont(font);
    hint.setString("Usa Arriba/Abajo o el mouse. Enter para seleccionar.");
    hint.setCharacterSize(16);
    hint.setPosition(10.f, 560.f);
}

void InterfazMenu::procesarEventos() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                textos[seleccionado].setFillColor(colorNormal);
                seleccionado = (seleccionado - 1 + textos.size()) % textos.size();
                textos[seleccionado].setFillColor(colorSeleccion);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                textos[seleccionado].setFillColor(colorNormal);
                seleccionado = (seleccionado + 1) % textos.size();
                textos[seleccionado].setFillColor(colorSeleccion);
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Dificultad seleccionada: " << opciones[seleccionado] << std::endl;
                window.close(); // Cierra el menú tras seleccionar
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePosF((float)event.mouseMove.x, (float)event.mouseMove.y);
            for (size_t i = 0; i < textos.size(); ++i) {
                if (textos[i].getGlobalBounds().contains(mousePosF)) {
                    if ((int)i != seleccionado) {
                        textos[seleccionado].setFillColor(colorNormal);
                        seleccionado = (int)i;
                        textos[seleccionado].setFillColor(colorSeleccion);
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosF((float)event.mouseButton.x, (float)event.mouseButton.y);
                for (size_t i = 0; i < textos.size(); ++i) {
                    if (textos[i].getGlobalBounds().contains(mousePosF)) {
                        std::cout << "Dificultad seleccionada (mouse): " << opciones[i] << std::endl;
                        seleccionado = (int)i;
                        window.close(); // Cierra el menú tras seleccionar
                    }
                }
            }
        }
    }
}

void InterfazMenu::dibujar() {
    window.clear(backgroundColor);
    window.draw(title);
    for (const auto& t : textos) window.draw(t);
    window.draw(hint);
    window.display();
}

void InterfazMenu::ejecutar() {
    while (window.isOpen() && running) {
        procesarEventos();
        dibujar();
    }
}

std::string InterfazMenu::getDificultadSeleccionada() const {
    return opciones[seleccionado];  // Devuelve la dificultad seleccionada
}