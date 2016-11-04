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
 
    m_x = double(xx);
    m_y = double(yy);
    m_z = double(zz);
 
 
}