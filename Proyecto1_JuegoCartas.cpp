#include <iostream>
#include "menu.h"
#include "rondas.h"

using namespace std;

//variables globales
int ronda = 1;

int main(){
    obtenerOpcionMenu(1, 3);
    while (ronda <= 3){
        cout << "Ronda " << ronda << endl;
        initRonda();
        ronda ++;
    }
    return 0;
}