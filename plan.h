////////////////////////////////////////////////////////////////////////////

// Projet P1RV - David Tuckey, Armand Cadet

// Fichier plan.h

///////////////////////////////////////////////////////////////////////////
#pragma once
#include "include.h"

class plan {
private:
    vertex *p1;
    vertex *p2;
    vertex *p3;
    vertex *p4;
    long nbre_triangles;
public:
    plan() {
        p1 = new vertex;
        p2 = new vertex;
        p3 = new vertex;
        p4 = new vertex;
    }
    vertex* getP1() { return p1;}
    vertex* getP2() { return p2;}
    vertex* getP3() { return p3;}
    vertex* getP4() { return p4;}
    long getNbre_triangles() { return nbre_triangles;}

    void setP1( vertex* _p1) { p1 = _p1; }
    void setP2( vertex* _p2) { p2 = _p2; }
    void setP3( vertex* _p3) { p3 = _p3; }
    void setP4( vertex* _p4) { p4 = _p4; }
    void setP1( vertex _p1 ) { p1->setX(_p1.getX()); p1->setY(_p1.getY()); p1->setZ(_p1.getZ()); }
    void setP2( vertex _p2 ) { p2->setX(_p2.getX()); p2->setY(_p2.getY()); p2->setZ(_p2.getZ()); }
    void setP3( vertex _p3 ) { p3->setX(_p3.getX()); p3->setY(_p3.getY()); p3->setZ(_p3.getZ()); }
    void setP4( vertex _p4 ) { p4->setX(_p4.getX()); p4->setY(_p4.getY()); p4->setZ(_p4.getZ()); }
    void setNbre_triangles( long _nbre_triangles) { nbre_triangles = _nbre_triangles; }


};
