#include <iostream>
#include "rondas.h"
using namespace std;
//elaborado por Guillermo Vivas

const char PICAS = 'P';
const char CORAZONES = 'C';
const char DIAMANTES = 'D';
const char TREBOLES = 'T';
const char JOKER = 'J';

struct Carta {
    int valor_numerico;
    char palo;

    Carta(int valor, char p) : valor_numerico(valor), palo(p) {}

    void mostrar_carta() {
        int valor = valor_numerico;
        if (valor >= 0 && valor <= 7) { // Rangos 0-7: 3 al 10
            cout << valor + 3;
        } else if (valor == 8) { // Rango 8: J
            cout << 'J';
        } else if (valor == 9) { // Rango 9: Q
            cout << 'Q';
        } else if (valor == 10) { // Rango 10: K
            cout << 'K';
        } else if (valor == 11) { // Rango 11: A
            cout << 'A';
        } else if (valor == 12) { // Rango 12: 2
            cout << '2';
        } else if (valor == 13 && palo == JOKER) { // Rango 13: Joker
            cout << "Joker";
        } else {
            cout << "Inv";
        }
        cout << palo;
    }
};

struct NodoCarta {
    Carta carta;
    NodoCarta* siguiente;

    NodoCarta(Carta c) : carta(c), siguiente(NULL) {}
};

struct PilaCartas {
    NodoCarta* cima;

    PilaCartas() : cima(nullptr) {}

    bool isVoid() {
        return cima == nullptr;
    }

    void push(Carta carta) {
        NodoCarta* nuevoNodo = new NodoCarta(carta);
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
    }

    Carta* top() {
        if (!isVoid()) {
            return &(cima->carta);
        }
        return nullptr;
    }

    Carta pop() {
        if (!isVoid()) {
            NodoCarta* temp = cima;
            Carta carta = cima->carta;
            cima = cima->siguiente;
            delete temp;
            return carta;
        }
        return Carta(-1, ' ');
    }
};

void pedirCartas(PilaCartas& jugadaTemporal, Jugador& jugador, int cantidad, int i = 0) {
    if (i == cantidad) return;

    cout << "Ingresa el valor (0=3 ... 13=Joker) de la carta #" << i + 1 << ": ";
    int valor;
    cin >> valor;

    cout << "Ingresa el palo (P, C, D, T o J para Joker): ";
    char palo;
    cin >> palo;

    NodoCarta* actual = jugador.mano.cima;
    NodoCarta* anterior = nullptr;
    bool encontrada = false;

    while (actual != nullptr) {
        if (actual->carta.valor_numerico == valor && actual->carta.palo == palo) {
            if (anterior == nullptr) {
                jugador.mano.cima = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            actual->siguiente = nullptr;
            jugadaTemporal.push(actual->carta);
            delete actual;
            encontrada = true;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!encontrada) {
        cout << "Carta no encontrada. Turno anulado." << endl;
        NodoCarta* temp = jugadaTemporal.cima;
        while (temp != nullptr) {
            jugador.mano.push(temp->carta);
            temp = temp->siguiente;
        }
        pasesConsecutivos++;
        return;
    }

    pedirCartas(jugadaTemporal, jugador, cantidad, i + 1);
}

void jugarTurno(int jugadorID) {
    Jugador& jugador = jugadores[jugadorID];
    cout << "\nTurno de " << jugador.nombre << endl;
    jugador.mano.mostrar_pila();

    cout << "¿Deseas pasar (0) o jugar cartas (1)? ";
    int opcion;
    cin >> opcion;

    if (opcion == 0) {
        cout << jugador.nombre << " ha pasado." << endl;
        pasesConsecutivos++;
        return;
    }

    cout << "¿Cuántas cartas deseas jugar? ";
    int cantidad;
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "Cantidad inválida. Turno perdido." << endl;
        pasesConsecutivos++;
        return;
    }

    PilaCartas jugadaTemporal;
    pedirCartas(jugadaTemporal, jugador, cantidad);

    // Validar la jugada
    if (!validarJugada(jugadaTemporal, jugadaActual)) {
        cout << "Jugada inválida. Pierdes el turno." << endl;
        NodoCarta* temp = jugadaTemporal.cima;
        while (temp != nullptr) {
            jugador.mano.push(temp->carta);
            temp = temp->siguiente;
        }
        pasesConsecutivos++;
        return;
    }

    // Jugada válida
    jugadaActual = jugadaTemporal;
    pasesConsecutivos = 0;
    cout << jugador.nombre << " jugó " << cantidad << " carta(s)." << endl;
}


    void mostrar_pila() {
        NodoCarta* actual = cima;
        cout << "Mano: ";
        while (actual != nullptr) {
            actual->carta.mostrar_carta();
            if (actual->siguiente != nullptr) {
                cout << ", ";
            }
            actual = actual->siguiente;
        }
        cout << endl;
    }

    ~PilaCartas() {
        NodoCarta* actual = cima;
        while (actual != nullptr) {
            NodoCarta* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cima = nullptr;
    }
};

int obtener_valor_jerarquico(int rango) {
    if (rango == 13) { // Joker
        return 20;
    }
    if (rango == 12) { // 2
        return 19;
    }
    if (rango == 11) { // As
        return 18;
    }
    // Para las cartas del 3 (rango 0) al Rey (rango 10)
    if (rango >= 0 && rango <= 10) {
        return rango;
    }
    return -1; // Valor inválido
}

bool es_mayor(int rango1, int rango2) {
    return obtener_valor_jerarquico(rango1) > obtener_valor_jerarquico(rango2);
}

int main() {
    PilaCartas manoJugador1;
    manoJugador1.push(Carta(0, PICAS));   // 3
    manoJugador1.push(Carta(11, CORAZONES)); // A

    PilaCartas manoJugador2;
    manoJugador2.push(Carta(12, TREBOLES));  // 2
    manoJugador2.push(Carta(8, PICAS));    // J

    PilaCartas manoJugador3;
    manoJugador3.push(Carta(7, DIAMANTES));  // 10
    manoJugador3.push(Carta(10, CORAZONES)); // K

    PilaCartas manoJugador4;
    manoJugador4.push(Carta(9, TREBOLES));  // Q
    manoJugador4.push(Carta(13, JOKER));    // Joker

    cout << "Mano del Jugador 1:" << endl;
    manoJugador1.mostrar_pila();
    cout << "Mano del Jugador 2:" << endl;
    manoJugador2.mostrar_pila();
    cout << "Mano del Jugador 3:" << endl;
    manoJugador3.mostrar_pila();
    cout << "Mano del Jugador 4:" << endl;
    manoJugador4.mostrar_pila();
    cout << endl;

    cout << "** Ronda de Juego (Simulación de la primera carta de cada jugador) **" << endl;

    Carta* carta_jugador1 = manoJugador1.top();
    Carta* carta_jugador2 = manoJugador2.top();
    Carta* carta_jugador3 = manoJugador3.top();
    Carta* carta_jugador4 = manoJugador4.top();

    cout << "Jugador 1 juega: "; if (carta_jugador1) carta_jugador1->mostrar_carta(); cout << endl;
    cout << "Jugador 2 juega: "; if (carta_jugador2) carta_jugador2->mostrar_carta(); cout << endl;
    cout << "Jugador 3 juega: "; if (carta_jugador3) carta_jugador3->mostrar_carta(); cout << endl;
    cout << "Jugador 4 juega: "; if (carta_jugador4) carta_jugador4->mostrar_carta(); cout << endl;
    cout << endl;

    return 0;
}