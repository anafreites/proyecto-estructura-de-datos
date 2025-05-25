#include <iostream>
#include "primitivas_pilas.h"
// #include "cartas.h"
// #include "rangos.h"


using namespace std;

//declaracion de un nodo tipo carta
struct NodeCartas {
    int rangoCartas; //valores de las cartas (del 0 al 12, siendo 0 = 3, 1 = 4... 12 = 2)
    int paloCartas; //0 = trebol, 1 = diamante, 2 = corazon, 3 = espada
    NodeCartas *next;
};

//declaracion de la lista de la cartas a parte para facilitar la cuenta de las cartas
struct listCartas {
    NodeCartas *head; //puntero a la primera carta del mazo
    int size; //para guardar el tamano de la mano de los jugadores
};

//caracteristicas de cada jugador
struct Jugador {
    listCartas mano; // mano del jugador
    bool turno; //saber si el jugador tuvo su turno
    char nombre[10]; //arreglo para guardar el nombre de los jugadores
};

//variables
listCartas mazo; //declaracion del mazo
Jugador jugadores[4]; //maximo de jugadores
NodeCartas *ultCarta = NULL; //ultima carta jugada
int jugadorActual = 0; //indice del jugador actual (para saber de quien es el turno)
int njugadores = 4; //numero total de jugadores

//funcion para intercambiar las cartas (se usara para ordenarlas)
void intercambiar (NodeCartas *a, NodeCartas *b){
    int auxRango = a -> rangoCartas; //auxiliares para no perder los valores del rango y palo de la primera carta
    int auxPalos = a -> paloCartas;
    a -> rangoCartas = b -> rangoCartas; 
    a -> paloCartas = b -> paloCartas;
    b -> rangoCartas = auxRango; //intercambio de los valores de las cartas
    b -> paloCartas = auxPalos;
}

//funcion para ordenar las cartas en las manos de los jugadores
void ordenarCartas (Jugador *p){
    if (p -> mano.size <= 1) return; //dejar la mano tal cual si el jugador no tiene cartas o tiene 1 sola
    int i = 0; //indice general
    NodeCartas *cartaActual;
    NodeCartas *sigCarta;
    while (i < p -> mano.size -1){ //para que el ciclo se repita hasta que todas las cartas esten ordenadas
        cartaActual = p -> mano.head; //la carta actual es la primera de la mano
        sigCarta = cartaActual -> next;
        int j = 0; //indice para recorrer la lista
        while (j < p -> mano.size - i - 1 && sigCarta != NULL){ //comparar cartas adyacentes
            if (cartaActual -> rangoCartas > sigCarta -> rangoCartas) intercambiar(cartaActual,sigCarta); //intercambiar si la carta tiene mayor rango que la que le sigue
            cartaActual = sigCarta;
            sigCarta = sigCarta -> next;
            j++;
        }
        i ++;
    }
}

//funcion para inicializar un mazo
void crear_mazo(){
    mazo.head = NULL;
    mazo.size = 0; //inicializamos el mazo en 0 para que este vacio
    int palo = 0;
    while (palo < 4){ //sabemos que el palo puede ser 0, 1, 2 y 3
        int rango = 0; //reiniciamos el rango de las cartas
        while (rango < 13){ //el rango va de 0 a 12
            push(&mazo, rango, palo);
            rango ++;
        }
        palo ++;
    }
}

//funcion para repartir cartas
void repartir() {
    int i = 0;
    //reiniciamos las manos de los jugadores para evitar usar cartas de rondas anteriores
    while (i < njugadores) {
        jugadores[i].mano.head = NULL;
        jugadores[i].mano.size = 0;
        i++;
    }
    i = 0;
    //empezamos a repartir las cartas
    while (mazo.head != NULL) {
        NodeCartas* carta = pop(&mazo);
        carta->next = jugadores[i].mano.head;
        jugadores[i].mano.head = carta;
        jugadores[i].mano.size++;
        i++;
        if (i >= njugadores) i = 0; //volvemos al primer jugador al terminar de repartirles a todos
    }
    i = 0;
    //ordenamos las cartas de los jugadores
    while (i < njugadores) {
        ordenarCartas(&jugadores[i]);
        i++;
    }
}

