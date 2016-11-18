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
        //cout<<(int) nTriChar<<" "<<(int) nTriChar[1]<<" "<<(int) nTriChar[2]<<" "<<(int) nTriChar[3]<<endl;;
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
  vector<vertex*> moy_norm;
  vector<vector<triangle*>> liste_triangle;

  nbre_norm.push_back(1);
  moy_norm.push_back(new vertex( v[0]->getN()->getX(), v[0]->getN()->getY(), v[0]->getN()->getZ() ) );
  vector<triangle*> newV;
	newV.push_back(v[0]);
	liste_triangle.push_back(newV);
  bool ok=false;
  for (unsigned int i=1; i<v.size(); i++) {
    cout<<"Traitement triangle "<<i<<endl;
    ok = true;
    for (unsigned int u=0; u<nbre_norm.size(); u++ ) {
        if (v[i]->comparerNormale( moy_norm[u], sensib ) ) {
          nbre_norm[u] += 1;
          liste_triangle[u].push_back(v[i]);
          calculerMoyenneNormales(liste_triangle[u], moy_norm[u]);
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
  for (unsigned int u =0; u<nbre_norm.size(); u++ ) {
	cout<<nbre_norm[u]<<endl;
    if ( nbre_norm[u] > nbre_norm[maxi] ) {
      maxi = u;
    }
  }
  cout<<nbre_norm[maxi]<<endl;
 //Code qui va chercher un vecteur perpendiculaire au premier basé sur sa perpendicularité au "sol" et du nombre de triangles dedans
    float sensibilites_test[4] = {0.001,0.01,0.1,1};
    int second = -1;
    for ( int i = 0; i<4 and second==-1; i++ ) {
        for (unsigned int u =0; u<nbre_norm.size(); u++ ) {
            if ( moy_norm[maxi]->scalaire(moy_norm[u]) > sensibilites_test[i]) {
                if ( second == -1 ) {
                    second = u;
                }
                else if ( nbre_norm[u] > nbre_norm[second] and u != maxi ) {
                    second = u;
                }

            }
        }
    }

    vertex* v1 = moy_norm[maxi];
    vertex* v2 = moy_norm[second];
    vertex* v3;
    //Projection du second vecteur pour qu'il soit perpendiculaire au premier, normalisation et création du troisième vecteur
    v1->normaliser();
    *v2 = *v2 - v2->scalaire(v1) * (*v1);
    cout<<"("<<v1->getX()<<","<<v1->getY()<<","<<v1->getZ()<<")"<<endl;
    v3 = v1->produitVectoriel(v2);

    cout<<"("<<v1->getX()<<","<<v1->getY()<<","<<v1->getZ()<<")"<<endl;
    cout<<"("<<v2->getX()<<","<<v2->getY()<<","<<v2->getZ()<<")"<<endl;
    cout<<"("<<v3->getX()<<","<<v3->getY()<<","<<v3->getZ()<<")"<<endl;


  return moy_norm[maxi];

}

void scene::calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale) {
    double x=0;
    double y=0;
    double z=0;

    for ( unsigned int i=0; i<triangles.size(); i++ ) {
      x += triangles[i]->getN()->getX();
      y += triangles[i]->getN()->getY();
      z += triangles[i]->getN()->getZ();

    }
    x = x/triangles.size();
    y = y/triangles.size();
    z = z/triangles.size();

    normale->setX(x);
    normale->setY(y);
    normale->setZ(z);
}
