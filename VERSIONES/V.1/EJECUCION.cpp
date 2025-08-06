#include <iostream>
#include <string>
#include "VAL_ESCRITURA.h"

void mostrarMenu() {
    cout << "=============================\n";
    cout << "     SELECCION DE MODO\n";
    cout << "=============================\n";
    cout << "1. Modo FAcil\n";
    cout << "2. Modo Intermedio\n";
    cout << "3. Modo DifIcil\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

void ejecutarModo(int opcion) {
    switch (opcion) {
        case 1:
            cout << "Enemigos lentos, mas vidas.\n";
            break;
        case 2:
            cout << "Equilibrio entre dificultad y recursos.\n";
            break;
        case 3:
            cout << "Enemigos rapidos, menos vidas.\n";
            break;
        case 4:
            cout << "\nGracias por jugar \n";
            break;
        default:
            cout << "\nOpcion invalida. Intenta nuevamente.\n";
    }
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cout << endl;
        ejecutarModo(opcion);
        cout << endl;
    } while (opcion != 4);

    return 0;
}

