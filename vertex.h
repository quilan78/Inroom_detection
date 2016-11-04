class vertex {
    public:
 
    vertex();
    vertex(char* bin);
    vertex(double _x, double _y, double _z);
    ~vertex();
 	private:
 		double x, y, z;
};