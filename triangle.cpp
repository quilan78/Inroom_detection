#include "include.h"

triangle::triangle(vertex* _p1, vertex* _p2, vertex* _p3, vertex* _n) {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    n = _n;
}

bool triangle::comparerNormale(triangle* t, float sensib) {
  return (( n->scalaire(t->getN()) > 1-sensib) or ( n->scalaire(t->getN()) < -1+sensib));
}

bool triangle::comparerNormale(vertex* _n, float sensib) {
  return (( n->scalaire(_n) > 1-sensib) or ( n->scalaire(_n) < -1+sensib ) );
}

vertex* triangle::moyenne() {
    vertex* retour = new vertex;
    retour->setX((p1->getX()+p2->getX()+p3->getX())/3);
    retour->setY((p1->getY()+p2->getY()+p3->getY())/3);
    retour->setZ((p1->getZ()+p2->getZ()+p3->getZ())/3);
    return retour;
}
