#include "include.h"
class triangle
{
    public:

    triangle();
    triangle(vertex* _p1, vertex* _p2, vertex* _p3, vertex* _n);
    void draw();
    ~triangle();

    private:
    vertex* p1;
    vertex* p2;
    vertex* p3;
    vertex* n;

};
