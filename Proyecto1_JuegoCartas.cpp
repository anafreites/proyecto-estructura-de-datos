#include <iostream>
#include "rondas.h"

using namespace std;

//variables globales
int ronda = 1;

int main(){
    while (ronda <= 3){
        cout << "Ronda " << ronda << endl;
        initRonda();
        ronda ++
    }
    return 0;
}