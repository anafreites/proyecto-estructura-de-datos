#include <iostream>
#include "rondas.h"
using namespace std;

struct Node {
    int value;
    Node *next;
};



int top(Node *p) {
    if (!p) return 0;
    else return p->value;
}

bool isVoid(Node *p) {
    if (!p) return true;
    return false;
}