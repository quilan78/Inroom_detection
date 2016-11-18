#include "include.h"
vertex::vertex(char* facet)
{
	char f1[4] = {facet[0],
		facet[1],facet[2],facet[3]};

	char f2[4] = {facet[4],
		facet[5],facet[6],facet[7]};

	char f3[4] = {facet[8],
		facet[9],facet[10],facet[11]};

	float xx = *((float*) f1 );
	float yy = *((float*) f2 );
	float zz = *((float*) f3 );

	x = double(xx);
	y = double(yy);
	z = double(zz);


}
vertex::vertex() {
    x=0;
    y=0;
    z=0;
}

vertex::vertex(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}

float vertex::norme() {
    return sqrt(x*x+y*y+z*z);
}

void vertex::normaliser() {
    float longueur = norme();
    x = x/longueur;
    cout<<longueur<<endl;
    y = y/longueur;
    z = z/longueur;
}

vertex* vertex::produitVectoriel(vertex* v) {
    vertex* sortie = new vertex();
    sortie->setX(y*v->getZ() - z*v->getY());
    sortie->setY(z*v->getX() - x*v->getZ());
    sortie->setX(x*v->getY() - y*v->getX());

    return sortie;
}

float vertex::scalaire(vertex* v) {
	 return sqrt(x*v->getX() + y*v->getY() + z*v->getZ());
}

vertex operator*(float a, vertex v) {
    vertex* sortie = new vertex();
    sortie->setX(a*v.getX());
    sortie->setY(a*v.getY());
    sortie->setZ(a*v.getZ());
    return *sortie;
}

vertex operator-(vertex const v, vertex const u) {
    vertex* sortie = new vertex();
    sortie->setX(v.getX()-u.getX());
    sortie->setY(v.getY()-u.getY());
    sortie->setZ(v.getZ()-u.getZ());
    return *sortie;
}

vertex operator+(vertex v, vertex u) {
    vertex* sortie = new vertex();
    sortie->setX(v.getX()+u.getX());
    sortie->setY(v.getY()+u.getY());
    sortie->setZ(v.getZ()+u.getZ());
    return *sortie;
}
