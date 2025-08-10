#ifndef VAL_LOGICAS_H
#define VAL_LOGICAS_H



#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


// Estructura para representar un jugador
struct Jugador {
	int puntaje;
	char eleccion; // 'A', 'B' o 'C'
	bool respuestaCorrecta;
	string nombre;
};

// Función para validar la respuesta del jugador
// Aquí solo compara dos strings, puedes adaptar para leer de archivo si lo necesitas
bool validarRespuesta(const string& respuestaJugador, const string& respuestaCorrecta) {
	return respuestaJugador == respuestaCorrecta;

}

#endif // VAL_LOGICAS_H

// Función para aplicar las reglas del juego
void aplicarReglas(Jugador &j1, Jugador &j2, int valorA, int valorB, int valorC) {
	// Ahora: si uno falla, el otro sí puede sumar/restar según la regla
	if (!j1.respuestaCorrecta && !j2.respuestaCorrecta) {
		cout << j1.nombre << " respondió mal y no suma puntos.\n";
		cout << j2.nombre << " respondió mal y no suma puntos.\n";
		return;
	}
	// Si solo j1 responde bien
	if (j1.respuestaCorrecta && !j2.respuestaCorrecta) {
		if (j1.eleccion == j2.eleccion) {
			if (j1.eleccion == 'A') { j1.puntaje += valorA; cout << j1.nombre << " suma " << valorA << " puntos.\n"; }
			else if (j1.eleccion == 'B') { j1.puntaje += valorB; cout << j1.nombre << " suma " << valorB << " puntos.\n"; }
			else { j1.puntaje += valorC; cout << j1.nombre << " suma " << valorC << " puntos.\n"; }
		} else if ((j1.eleccion == 'A' && j2.eleccion == 'C')) {
			j1.puntaje += valorB; cout << j1.nombre << " suma " << valorB << " puntos.\n"; }
		else if ((j1.eleccion == 'C' && j2.eleccion == 'A')) {
			j1.puntaje += (valorC - 5); cout << j1.nombre << " suma " << (valorC - 5) << " puntos.\n"; }
		else if ((j1.eleccion == 'B' && j2.eleccion == 'C')) {
			j1.puntaje += valorB; cout << j1.nombre << " suma " << valorB << " puntos.\n"; }
		else if ((j1.eleccion == 'C' && j2.eleccion == 'B')) {
			j1.puntaje += valorC; cout << j1.nombre << " suma " << valorC << " puntos.\n"; }
		else if ((j1.eleccion == 'A' && j2.eleccion == 'B')) {
			j1.puntaje -= 20; cout << j1.nombre << " pierde 20 puntos.\n"; }
		else if ((j1.eleccion == 'B' && j2.eleccion == 'A')) {
			j1.puntaje -= 10; cout << j1.nombre << " pierde 10 puntos.\n"; }
		cout << j2.nombre << " respondió mal y no suma puntos.\n";
		return;
	}
	// Si solo j2 responde bien
	if (!j1.respuestaCorrecta && j2.respuestaCorrecta) {
		if (j1.eleccion == j2.eleccion) {
			if (j2.eleccion == 'A') { j2.puntaje += valorA; cout << j2.nombre << " suma " << valorA << " puntos.\n"; }
			else if (j2.eleccion == 'B') { j2.puntaje += valorB; cout << j2.nombre << " suma " << valorB << " puntos.\n"; }
			else { j2.puntaje += valorC; cout << j2.nombre << " suma " << valorC << " puntos.\n"; }
		} else if ((j2.eleccion == 'A' && j1.eleccion == 'C')) {
			j2.puntaje += valorB; cout << j2.nombre << " suma " << valorB << " puntos.\n"; }
		else if ((j2.eleccion == 'C' && j1.eleccion == 'A')) {
			j2.puntaje += (valorC - 5); cout << j2.nombre << " suma " << (valorC - 5) << " puntos.\n"; }
		else if ((j2.eleccion == 'B' && j1.eleccion == 'C')) {
			j2.puntaje += valorB; cout << j2.nombre << " suma " << valorB << " puntos.\n"; }
		else if ((j2.eleccion == 'C' && j1.eleccion == 'B')) {
			j2.puntaje += valorC; cout << j2.nombre << " suma " << valorC << " puntos.\n"; }
		else if ((j2.eleccion == 'A' && j1.eleccion == 'B')) {
			j2.puntaje -= 20; cout << j2.nombre << " pierde 20 puntos.\n"; }
		else if ((j2.eleccion == 'B' && j1.eleccion == 'A')) {
			j2.puntaje -= 10; cout << j2.nombre << " pierde 10 puntos.\n"; }
		cout << j1.nombre << " respondió mal y no suma puntos.\n";
		return;
	}
	// Si ambos responden bien, aplicar reglas normales
	if (j1.respuestaCorrecta && j2.respuestaCorrecta) {
		if (j1.eleccion == j2.eleccion) {
			if (j1.eleccion == 'A') { j1.puntaje += valorA; j2.puntaje += valorA; cout << j1.nombre << " suma " << valorA << " puntos.\n"; cout << j2.nombre << " suma " << valorA << " puntos.\n"; }
			else if (j1.eleccion == 'B') { j1.puntaje += valorB; j2.puntaje += valorB; cout << j1.nombre << " suma " << valorB << " puntos.\n"; cout << j2.nombre << " suma " << valorB << " puntos.\n"; }
			else { j1.puntaje += valorC; j2.puntaje += valorC; cout << j1.nombre << " suma " << valorC << " puntos.\n"; cout << j2.nombre << " suma " << valorC << " puntos.\n"; }
		}
		else if ((j1.eleccion == 'A' && j2.eleccion == 'C') || (j1.eleccion == 'C' && j2.eleccion == 'A')) {
			if (j1.eleccion == 'C') { j1.puntaje += (valorC - 5); j2.puntaje += valorB; cout << j1.nombre << " suma " << (valorC - 5) << " puntos.\n"; cout << j2.nombre << " suma " << valorB << " puntos.\n"; }
			else { j2.puntaje += (valorC - 5); j1.puntaje += valorB; cout << j2.nombre << " suma " << (valorC - 5) << " puntos.\n"; cout << j1.nombre << " suma " << valorB << " puntos.\n"; }
		}
		else if ((j1.eleccion == 'B' && j2.eleccion == 'C') || (j1.eleccion == 'C' && j2.eleccion == 'B')) {
			if (j1.eleccion == 'B') { j1.puntaje += valorB; j2.puntaje += valorC; cout << j1.nombre << " suma " << valorB << " puntos.\n"; cout << j2.nombre << " suma " << valorC << " puntos.\n"; }
			else { j2.puntaje += valorB; j1.puntaje += valorC; cout << j2.nombre << " suma " << valorB << " puntos.\n"; cout << j1.nombre << " suma " << valorC << " puntos.\n"; }
		}
		else if ((j1.eleccion == 'A' && j2.eleccion == 'B') || (j1.eleccion == 'B' && j2.eleccion == 'A')) {
			if (j1.eleccion == 'B') { j1.puntaje -= 10; j2.puntaje -= 20; cout << j1.nombre << " pierde 10 puntos.\n"; cout << j2.nombre << " pierde 20 puntos.\n"; }
			else { j2.puntaje -= 10; j1.puntaje -= 20; cout << j2.nombre << " pierde 10 puntos.\n"; cout << j1.nombre << " pierde 20 puntos.\n"; }
		}
	}
}


#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Pregunta {
	string enunciado;
	string opciones[3];
	char respuestaCorrecta; // 'A', 'B' o 'C'
};

vector<Pregunta> cargarPreguntas(const string& archivo) {
	vector<Pregunta> preguntas;
	ifstream file(archivo);
	string linea;
	while (getline(file, linea)) {
		// Saltar líneas vacías y comentarios
		while ((linea.empty() || linea[0] == '#') && getline(file, linea));
		if (file.eof() || linea.empty() || linea[0] == '#') break;
		Pregunta p;
		p.enunciado = linea;
		bool completa = true;
		for (int i = 0; i < 3; ++i) {
			while (getline(file, linea) && (linea.empty() || linea[0] == '#')) {}
			if (file.eof() || linea.empty() || linea[0] == '#') { completa = false; break; }
			p.opciones[i] = linea;
		}
		if (!completa) continue;
		while (getline(file, linea) && (linea.empty() || linea[0] == '#')) {}
		if (file.eof() || linea.empty() || linea[0] == '#') continue;
		p.respuestaCorrecta = linea[0];
		preguntas.push_back(p);
	}
	return preguntas;
}


// Función interactiva mejorada: cada jugador elige camino, ve su puntaje y responde una pregunta aleatoria
void rondaInteractiva(Jugador &j1, Jugador &j2) {
	vector<Pregunta> preguntas = cargarPreguntas("c:/Users/chica/OneDrive/Desktop/prueba juego modelos/Modelos-discretos-/DATA_BASE/EJEMPLO_DE_PREGUNTAS.txt");
	if (preguntas.size() < 2) {
		cout << "No hay suficientes preguntas para ambos jugadores.\n";
		return;
	}
	srand((unsigned)time(0));
	// Valores aleatorios para los caminos (A < B < C)
	int valorA = 5 + rand() % 6; // 5-10
	int valorB = valorA + 5;
	int valorC = valorB + 5;

	// --- JUGADOR 1 ---
	cout << "\n" << j1.nombre << ", tienes " << j1.puntaje << " puntos." << endl;
	cout << "Elige tu camino (A/B/C): ";
	cin >> j1.eleccion;
	int idx1 = rand() % preguntas.size();
	Pregunta pregunta1 = preguntas[idx1];
	cout << "\nPregunta para " << j1.nombre << ":\n" << pregunta1.enunciado << endl;
	for (int i = 0; i < 3; ++i) cout << pregunta1.opciones[i] << endl;
	cout << "Tu respuesta: ";
	string respJ1;
	cin.ignore();
	getline(cin, respJ1);
	j1.respuestaCorrecta = (toupper(respJ1[0]) == pregunta1.respuestaCorrecta);
	if (j1.respuestaCorrecta)
		cout << "¡Correcto!" << endl;
	else
		cout << "Incorrecto. La respuesta correcta era: " << pregunta1.respuestaCorrecta << endl;

	// --- JUGADOR 2 ---
	cout << "\n" << j2.nombre << ", tienes " << j2.puntaje << " puntos." << endl;
	cout << "Elige tu camino (A/B/C): ";
	cin >> j2.eleccion;
	int idx2;
	do { idx2 = rand() % preguntas.size(); } while (idx2 == idx1 && preguntas.size() > 1);
	Pregunta pregunta2 = preguntas[idx2];
	cout << "\nPregunta para " << j2.nombre << ":\n" << pregunta2.enunciado << endl;
	for (int i = 0; i < 3; ++i) cout << pregunta2.opciones[i] << endl;
	cout << "Tu respuesta: ";
	string respJ2;
	cin.ignore();
	getline(cin, respJ2);
	j2.respuestaCorrecta = (toupper(respJ2[0]) == pregunta2.respuestaCorrecta);
	if (j2.respuestaCorrecta)
		cout << "¡Correcto!" << endl;
	else
		cout << "Incorrecto. La respuesta correcta era: " << pregunta2.respuestaCorrecta << endl;

	// --- APLICAR REGLAS Y MOSTRAR RESULTADOS ---
	aplicarReglas(j1, j2, valorA, valorB, valorC);

	cout << "\nValores de caminos: A=" << valorA << ", B=" << valorB << ", C=" << valorC << endl;
	cout << "Puntaje final " << j1.nombre << ": " << j1.puntaje << endl;
	cout << "Puntaje final " << j2.nombre << ": " << j2.puntaje << endl;
}
