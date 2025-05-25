#include <iostream>
using namespace std;

struct Node {
    int value;
    Node *next;
};

void push(Node **p, int value) {
    Node *newElement = new Node;
    newElement->value = value;
    newElement->next = *p;
    *p = newElement;
}

int pop(Node **p) {
    if (!(*p)) return 0;
    Node *aux = *p;
    int value = (*p)->value;
    *p = (*p)->next;
    delete aux;
    return value;
}

int top(Node *p) {
    if (!p) return 0;
    else return p->value;
}

bool isVoid(Node *p) {
    if (!p) return true;
    return false;
}