////////////////////////////////////////////////////////////////////////////

// Projet P1RV - David Tuckey, Armand Cadet

// Fichier vertex.h

///////////////////////////////////////////////////////////////////////////
class vertex {
    public:

    vertex();
    vertex(char* bin);
    vertex( vertex* v);
    vertex(double _x, double _y, double _z);
    ~vertex() {}
    double getX() const{ return x; }
    double getY() const{ return y; }
    double getZ() const{ return z; }
    void setX( double _x ) { x=_x;  }
    void setY( double _y ) { y=_y; }
    void setZ( double _z ) { z=_z; }
    vertex* produitVectoriel(vertex* v);
    void normaliser();
    float norme();
    void soustraction(vertex* v);
    void multiplication(double a);
    float scalaire(vertex* v);
 	private:
 		double x, y, z;
};
vertex operator+(vertex v, vertex u);
vertex operator-(vertex v, vertex u);
vertex operator*(double a, vertex v);
ostream& operator<<( ostream& s, vertex* v);
ostream& operator<<( ostream& s, vertex v);
