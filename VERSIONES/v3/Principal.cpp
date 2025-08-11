#include "InterfazMenu.h"
#include "InterfazJuego.h"
#include <string>

int main() {
    // Crear y ejecutar el menú
    InterfazMenu menu;
    menu.ejecutar();

    // Obtener la dificultad seleccionada
    std::string dificultad = menu.getDificultadSeleccionada();

    // Crear e iniciar el juego
    InterfazJuego juego(dificultad);
    juego.iniciar();

    return 0;
}
