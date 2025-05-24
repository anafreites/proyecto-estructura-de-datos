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
cartas mazo[54]; // numero total de cartas
jugador jugadores[4]; //maximo de jugadores
int jugadorActual = 0; //indice del jugador actual (para saber de quien es el turno)
int njugadores = 4; //numero total de jugadores

//funcion para intercambiar las cartas (se usara para ordenarlas)
void intercambiar (cartas *a, cartas *b){
    cartas aux = *a; //auxiliar para no perder el valor de la primera carta
    *a = *b;
    *b = aux;

}

//funcion para ordenar las cartas en las manos de los jugadores
void ordenar_cartas (jugador *p){
    int i = 0;
    while (i < p -> tamano_mano -1){ //indice menor a lo que esta apuntando p menos 1
        int j = i + 1; //indice auxiliar
        while (j < p -> tamano_mano){ //indice menor a lo que esta apuntando p
            if (p -> mano[i].rango_cartas > p -> mano[j].rango_cartas){ //comparacion de dos cartas dentro del arreglo
                intercambiar(&p -> mano[i], &p -> mano[j]);
            }
            j ++;
        }
        i ++;
    }
}

//funcion para inicializar un mazo
void crear_mazo(){
    int i = 0; //indice general
    int p = 0; //indice de los palos de las cartas (0 = trebol, 1 = diamante, 2 = corazon, 3 = espada)
    while (p < 4){
        int r = 0; //indice del rango de las cartas (del 0 al 12)
        while (r < 13){
            mazo[i].rango_cartas = r; //asignacion del rango de la carta
            mazo[i].palo = p; //asignacion del palo de la carta
            i ++;
            r ++;
        }
        p ++;
    }
}

//funcion para repartir cartas
void repartir(){
    int i = 0; //indice general
    while (i < njugadores){ //reiniciar el tamano de las manos para no usar cartas de rondas anteriores
        jugadores[i].tamano_mano = 0;
        i ++;
    }

    int j = 0; //indice auxiliar
    int p = 0; //indice del jugador actual
    while (j < 54){
        jugadores[p].mano[jugadores[p].tamano_mano] = mazo[j]; //darle na carta a un jugador
        jugadores[p].tamano_mano ++; //aumentar el tamano de la mano de dicho jugador
        j ++;
        p ++;
        if (p >= njugadores) p = 0; //volver al primer jugador despues de repartir
    }
    i = 0; //reiniciamos el indice para ordenar las cartas de los jugadores
    while (i < njugadores){
        ordenar_cartas(&jugadores[i]); //ordenamos la mano de c/jugador despues de repartir las cartas
        i ++;
    }

}
