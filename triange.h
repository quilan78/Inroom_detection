class triangle
{
    public:

    triangle();
    triangle(vertex* _p1, vertex* _p2, vertex* _p3, vertex* _n);
    void draw();
    ~triangle();

    vertex* p1, p2, p3, n;

};
