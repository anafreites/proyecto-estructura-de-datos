#include <iostream>
#include "menu.h"
#include "rondas.h"
#include "cartas.h"

using namespace std;

//variables globales
int ronda = 1;
int turno;

int main(){
    obtenerOpcionMenu(1, 3);
    while (ronda < 4){
        cout << "Ronda #" << ronda << endl;
        initRonda(ronda);
        ronda ++;
    }
    return 0;
}