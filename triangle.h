////////////////////////////////////////////////////////////////////////////

// Projet P1RV - David Tuckey, Armand Cadet

// Fichier triangle.h

///////////////////////////////////////////////////////////////////////////
#include "include.h"
class triangle
{
    public:

    triangle();
    triangle(vertex* _p1, vertex* _p2, vertex* _p3, vertex* _n);
    void draw();
    ~triangle();
    bool comparerNormale(triangle* t, float sensib);
    bool comparerNormale(vertex* n, float sensib);
    vertex* getN() { return n; }
    vertex* getP1() { return p1; }
    vertex* getP2() { return p2; }
    vertex* getP3() { return p3; }
    void setN( vertex* _n ) { n = _n;}
    vertex* moyenne();
    private:
    vertex* p1;
    vertex* p2;
    vertex* p3;
    vertex* n;

};
