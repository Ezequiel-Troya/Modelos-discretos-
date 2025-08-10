#include "VAL_LOGICAS.h"

int main() {
    Jugador j1 = {10, 'A', false, "Jugador1"};
    Jugador j2 = {10, 'A', false, "Jugador2"};
    for (int i = 1; i <= 3; ++i) {
        cout << "\n================ RONDA " << i << " ================\n";
        rondaInteractiva(j1, j2);
    }
    cout << "\nPUNTAJE FINAL TRAS 3 RONDAS:" << endl;
    cout << j1.nombre << ": " << j1.puntaje << endl;
    cout << j2.nombre << ": " << j2.puntaje << endl;
    return 0;
}
