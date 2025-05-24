#include <iostream>
// #include "cartas.h"
// #include "rangos.h"

using namespace std;

struct cartas {
    int rango_cartas; //valores de las cartas
    int palo; //0 = trebol, 1 = diamante, 2 = corazon, 3 = espada
};

struct jugador {
    cartas mano[13]; // mano del jugador
    int tamano_mano; // cantidad de cartas de c/jugador
    int turno; //saber si el jugador tuvo su turno
};

//variables
cartas mazo[52]; // numero total de cartas
jugador jugadores[4]; //maximo de jugadores
int jugadorActual = 0; //indice del jugador actual (para saber de quien es el turno)

//funcion para intercambiar las cartas (se usara para ordenarlas)
void intercambiar (cartas *a, cartas *b){
    cartas aux = *a;
    *a = *b;
    *b = aux;

}

//funcion para ordenar las cartas en las manos de los jugadores
void ordenar_cartas (jugador *p){
    int i = 0;
    while (i < p -> tamano_mano -1){
        int j = i + 1;
        while (j < p -> tamano_mano){
            if (p -> mano[i].rango_cartas > p -> mano[j].rango_cartas){
                intercambiar(&p -> mano[i], &p -> mano[j]);
            }
            j ++;
        }
        i ++;
    }
}