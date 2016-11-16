class vertex {
    public:

    vertex();
    vertex(char* bin);
    vertex(double _x, double _y, double _z);
    ~vertex();
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    void setX( double _x ) { x=_x; }
    void setY( double _y ) { y=_y; }
    void setZ( double _z ) { z=_z; }

    float scalaire(vertex* v);
 	private:
 		double x, y, z;
};
