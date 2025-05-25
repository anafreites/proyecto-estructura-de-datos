#include <iostream>
#include "rondas.h"
using namespace std;

struct Node {
    int value;
    Node *next;
};

void push(listCartas *p, int rangoCartas, int paloCartas) {
    NodeCartas *newElement = new NodeCartas;
    newElement -> rangoCartas = rangoCartas;
    newElement -> paloCartas = paloCartas;
    newElement -> next = p -> head;
    p -> head = newElement;
    p -> size ++;
}

int pop(listaCartas *p) {
    if (!(*p)) return 0;
    NodeCartas *aux = p -> head;
    p -> head = (p -> head) -> next;
    p -> size --;
    delete aux;
    return aux;
}

int top(Node *p) {
    if (!p) return 0;
    else return p->value;
}

bool isVoid(Node *p) {
    if (!p) return true;
    return false;
}