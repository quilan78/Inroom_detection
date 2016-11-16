#include "include.h"

unsigned long scene::read_stl(string fname){

    //!!
    //don't forget ios::binary
    //!!
    ifstream myFile ( fname.c_str(), ios::in | ios::binary);

    char header_info[80] = "";
    char nTriChar[4];
    unsigned long nTri = 0;

    char trash[2];

    //read 80 byte header
    if (myFile) {
        myFile.read (header_info, 80);
        myFile.read(nTriChar, 4);
        cout<<(int) nTriChar<<" "<<(int) nTriChar[1]<<" "<<(int) nTriChar[2]<<" "<<(int) nTriChar[3]<<endl;;
        nTri = *((unsigned long*)nTriChar);

        for (unsigned long i=0; i<nTri; i++) {
            char vertexchar[12];

            myFile.read(vertexchar, 12);
            vertex* normal = new vertex(vertexchar);

            myFile.read(vertexchar, 12);
            vertex* p1 = new vertex(vertexchar);

            myFile.read(vertexchar, 12);
            vertex* p2 = new vertex(vertexchar);

            myFile.read(vertexchar, 12);
            vertex* p3 = new vertex(vertexchar);

            v.push_back( new triangle(p1, p2, p3, normal));
            myFile.read(trash, 2);
        }
    }
    return nTri;
}

vertex* scene::getNormaleMaxixmum(float sensib) {
  vector<int> nbre_norm;
  verctor<vertex*> moy_norm;
  vector<vector<triangle*>> liste_triangle;

  nbre_norm.push_back(1);
  moy_norm.push_back(new vertex( v[0]->getN()->getX(), v[0]->getN()->getY(), v[0]->getN()->getZ() ) );
  bool ok=false;
  for ( int i=1; i<v.size(); i++) {
    ok = true;
    for ( int u=0; u<nbre_norm.size(); u++ ) {
        if (v[i]->comparerNormale( moy_norm[u], sensib ) ) {
          nbre_norm[u] += 1;
          liste_triangle[u].push_back(v[i]);
          calculerMoyenneNormales(liste_triangles[u], moy_norm[u]);
          ok = false;
        }
    }
    if ( ok ) {
      nbre_norm.push_back(0);
      vector<triangle*> newV;
      newV.push_back(v[i]);
      liste_triangle.push_back(newV);
      moy_norm.push_back(new vertex( v[i]->getN()->getX(), v[i]->getN()->getY(), v[i]->getN()->getZ() ) );

    }
  }
  int maxi=0;
  for ( int u =0; u<nbre_norm.size(); u++ ) {
    if ( nbre_norm[u] > nbre_norm[maxi] ) {
      maxi = u;
    }
  }

  return moy_norm[maxi];

}

void scene::calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale) {
    double x=0;
    double y=0;
    double z=0;

    for ( int i=0; i<triangles.size(); i++ ) {
      x += triangle->getN()->getX();
      y += triangle->getN()->getY();
      z += triangle->getN()->getZ();

    }
    x = x/triangles.size();
    y = y/triangles.size();
    z = z/triangles.size();

    normale.setX(x);
    normale.setY(y);
    normale.setZ(z);
}
