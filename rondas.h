#include <iostream>
// #include "cartas.h"
// #include "rangos.h"

using namespace std;

struct cartas {
    int rango;
    int palo; //0 = trebol, 1 = diamante, 2 = corazon, 3 = espada
};

struct jugador {
    cartas mano[13];
    int tamano_mano;
    int turno;
};
