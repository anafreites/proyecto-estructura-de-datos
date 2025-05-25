#include <iostream>
#include "rondas.h"
using namespace std;

struct Node {
    int value;
    Node *next;
};

void push(listCartas *p, int rangoCartas, int paloCartas) {
    NodeCartas *newElement = new NodeCartas;
    newElement->rangoCartas = rangoCartas;
    newElement->paloCartas = paloCartas;
    newElement->next = p->head;
    p->head = newElement;
    p->size++;
}

NodeCartas* pop(listCartas *p) {
    if (!p || !(p->head)) return NULL;
    NodeCartas *aux = p->head;
    p->head = p->head->next;
    p->size--;
    aux->next = NULL;
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