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
            //cout<<p1<<p2<<p3;
            v.push_back( new triangle(p1, p2, p3, normal));
            myFile.read(trash, 2);
        }
    }
    return nTri;
}

void scene::write_stl(string fname){
  if(fname.size() == 0) {
    fname = "file.stl";
  } else if(fname.find(".stl", fname.size()-4)) {
    fname += ".stl";
  }
  ofstream myFile (fname.c_str(), ios::out | ios::binary);
  for(int i = 0; i < 80; i++) {
    myFile << '\0';
  }
  char attribute[2] = "0";
  unsigned long size = v.size();
  if(!size) {
    cout<<"Warning : writing empty STL file";
  }
  myFile << (char)(size & 0xFF) << (char)((size >> 8) & 0xFF) << (char)((size >> 16) & 0xFF) << (char)((size >> 24) & 0xFF);
  for(unsigned long i = 0; i < size; i++) {
    /*myFile.write((char*)&(v[i]->getN()->getX()), 4);
    myFile.write((char*)&(v[i]->getN()->getY()), 4);
    myFile.write((char*)&(v[i]->getN()->getZ()), 4);

    myFile.write((char*)&(v[i]->getP1()->getX()), 4);
    myFile.write((char*)&(v[i]->getP1()->getY()), 4);
    myFile.write((char*)&(v[i]->getP1()->getZ()), 4);

    myFile.write((char*)&(v[i]->getP2()->getX()), 4);
    myFile.write((char*)&(v[i]->getP2()->getY()), 4);
    myFile.write((char*)&(v[i]->getP2()->getZ()), 4);

    myFile.write((char*)&(v[i]->getP3()->getX()), 4);
    myFile.write((char*)&(v[i]->getP3()->getY()), 4);
    myFile.write((char*)&(v[i]->getP3()->getZ()), 4);/
    myFile.write(attribute,2);*/
    //myFile  << v[i].getNorm() << v[i].getP1() << v[i].getP2() << v[i].getP3() << '\0' << '\0';
  }
}

void scene::algoSansProjection(float sensib_scalaire, float sensib_hauteur) {
  vector<long> nbre_norm;
  vector<vertex*> moy_norm;
  vector<vector<triangle*>> liste_triangle;

  nbre_norm.push_back(1);
  moy_norm.push_back(new vertex( v[0]->getN()->getX(), v[0]->getN()->getY(), v[0]->getN()->getZ() ) );
  vector<triangle*> newV;
  newV.push_back(v[0]);
  liste_triangle.push_back(newV);

  //cout<<v[0]->getP1()<<v[0]->getP2()<<v[0]->getP3();
  bool ok=false;
  for (unsigned int i=1; i<v.size(); i++) {
    if ( i % 1000 == 0) {
        cout<<"Traitement triangle "<<i<<endl;
    }
    ok = true;
    for (unsigned int u=0; u<nbre_norm.size(); u++ ) { // On parcours les groupes existants � cette boucle
        if (v[i]->comparerNormale( moy_norm[u], sensib_scalaire ) ) { // On v�rifie si le vecteur appartient au groupe u
          nbre_norm[u] += 1;
          liste_triangle[u].push_back(v[i]);
          calculerMoyenneNormales(liste_triangle[u], moy_norm[u]);
          ok = false;
        }
    }
    if ( ok ) { //Ce triangle n'appartient � aucun autre des groupes, on lui cr�e un nouyeau groupe
      nbre_norm.push_back(0);
      vector<triangle*> newV;
      newV.push_back(v[i]);
      liste_triangle.push_back(newV);
      moy_norm.push_back(new vertex( v[i]->getN()->getX(), v[i]->getN()->getY(), v[i]->getN()->getZ() ) );

    }
  }



	for(unsigned int i=0; i<nbre_norm; i++ ){
		vertex* axe2 = new vertex(-moy_norm[i]->getY(), moy_norm[i]->getX(), 0 );
		axe2->normaliser();
		vertex* axe3 = moy_norm[i]->produitVectoriel(axe2);
		detectionPlan( sensib_hauteur, liste_triangle[i], moy_norm[i], axe2, axe3 )

	}
}


vertex* scene::createBase(float sensib) {
  vector<long> nbre_norm;
  vector<vertex*> moy_norm;
  vector<vector<triangle*>> liste_triangle;

  nbre_norm.push_back(1);
  moy_norm.push_back(new vertex( v[0]->getN()->getX(), v[0]->getN()->getY(), v[0]->getN()->getZ() ) );
  vector<triangle*> newV;
  newV.push_back(v[0]);
  liste_triangle.push_back(newV);

  //cout<<v[0]->getP1()<<v[0]->getP2()<<v[0]->getP3();
  bool ok=false;
  for (unsigned int i=1; i<v.size(); i++) {
    if ( i % 1000 == 0) {
        cout<<"Traitement triangle "<<i<<endl;
    }
    ok = true;
    for (unsigned int u=0; u<nbre_norm.size(); u++ ) { // On parcours les groupes existants � cette boucle
        if (v[i]->comparerNormale( moy_norm[u], sensib ) ) { // On v�rifie si le vecteur appartient au groupe u
          nbre_norm[u] += 1;
          liste_triangle[u].push_back(v[i]);
          calculerMoyenneNormales(liste_triangle[u], moy_norm[u]);
          ok = false;
        }
    }
    if ( ok ) { //Ce triangle n'appartient � aucun autre des groupes, on lui cr�e un nouyeau groupe
      nbre_norm.push_back(0);
      vector<triangle*> newV;
      newV.push_back(v[i]);
      liste_triangle.push_back(newV);
      moy_norm.push_back(new vertex( v[i]->getN()->getX(), v[i]->getN()->getY(), v[i]->getN()->getZ() ) );

    }
  }

  //On cherche la direction o� il y en a le plus
  unsigned int maxi=0;
  for (unsigned int u =0; u<nbre_norm.size(); u++ ) {
	cout<<nbre_norm[u]<<endl;
    if ( nbre_norm[u] > nbre_norm[maxi] ) {
      maxi = u;
    }
  }
  cout<<nbre_norm[maxi]<<endl;

 //Code qui va chercher un vecteur perpendiculaire au premier bas� sur sa perpendicularit� au "sol" et du nombre de triangles dedans
    float sensibilites_test[4] = {0.001,0.01,0.1,1};
    int second = -1;
    for ( int i = 0; i<4 and second==-1; i++ ) {
        cout<<sensibilites_test[i]<<endl;

        for (unsigned int u =0; u<nbre_norm.size(); u++ ) {
            if ( abs(moy_norm[maxi]->scalaire(moy_norm[u])) < sensibilites_test[i]) {
                if ( second == -1 ) {
                    second = u;
                }
                else if ( nbre_norm[u] > nbre_norm[second] and u != maxi ) {
                    second = u;
                }

            }
        }
    }
    v1 = moy_norm[maxi];
    v2 = moy_norm[second];

    //Projection du second vecteur pour qu'il soit perpendiculaire au premier, normalisation et cr�ation du troisi�me vecteur
    v1->normaliser();
    *v2 = *v2 - v2->scalaire(v1) * (*v1);
    vertex* v4 = new vertex;
    v2->normaliser();
    v3 = v1->produitVectoriel(v2);
    cout<<v1->norme()<<endl;
    cout<<v2->norme()<<endl;
    cout<<v3->norme()<<endl;
    cout<<"("<<v1->getX()<<","<<v1->getY()<<","<<v1->getZ()<<")"<<endl;
    cout<<"("<<v2->getX()<<","<<v2->getY()<<","<<v2->getZ()<<")"<<endl;
    cout<<"("<<v3->getX()<<","<<v3->getY()<<","<<v3->getZ()<<")"<<endl;
    cout<<v2->scalaire(v1)<<endl;
    cout<<v2->scalaire(v3)<<endl;
    cout<<v1->scalaire(v3)<<endl;


  return moy_norm[maxi];

}

void scene::calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale) {
    // On passe le vertex � modifier en argument
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

void scene::projeterTriangles() {
    for (unsigned int i=1; i<v.size(); i++) {
        double a = v[i]->getN()->scalaire(v1);
        double b = v[i]->getN()->scalaire(v2);
        double c = v[i]->getN()->scalaire(v3);
        //cout<<a<<" "<<b<<" "<<c<<endl;
        if (a > b and a > c) {
            v[i]->setN(v1);
            proj_v1.push_back(v[i]);
        }
        else if ( b >a and  b>c ) {
            v[i]->setN(v2);
            proj_v2.push_back(v[i]);
        }
        else {
            v[i]->setN(v3);
            proj_v3.push_back(v[i]);
        }

    }
}

void scene::detectionPlanV1(double sensib) {
    detectionPlan(sensib, proj_v1, v1, v2, v3 );
}

void scene::detectionPlanV2(double sensib) {
    detectionPlan(sensib, proj_v2, v2, v3, v1 );
}

void scene::detectionPlanV3(double sensib) {
    detectionPlan(sensib, proj_v3, v3, v1, v2 );
}

void scene::detectionPlan(double sensib, vector<triangle*>triangles, vertex* axe1, vertex* axe2, vertex* axe3 ) {
    vector<vector<vertex*> > plan_detectes; // Va stocker les groupes de plans
    vector<double> hauteur_detectes; // Va stocker les hauteurs moyennes des diff�rents groupes
    bool ok;
    vector<vertex*> newV;
    newV.push_back(triangles[0]->moyenne());
    plan_detectes.push_back(newV);
    hauteur_detectes.push_back(triangles[0]->moyenne()->scalaire(axe1));

    //cout<<"hello1"<<endl;

    for(unsigned int i=1; i<triangles.size(); i++) { // On parcours tous les triangles de la liste
        ok = true;
        for (unsigned int u=0; u<hauteur_detectes.size(); u++ ) { // On parcours les groupes existants � cette boucle
            if (triangles[i]->moyenne()->scalaire(axe1) > hauteur_detectes[u]-sensib and triangles[i]->moyenne()->scalaire(axe1) < hauteur_detectes[u]+sensib ) { // On v�rifie si le vecteur appartient au groupe u
                plan_detectes[u].push_back(triangles[i]->moyenne());
                hauteur_detectes[u] = calculerHauteurMoyenne(plan_detectes[u], axe1);
                ok = false;
            }
        }
        if ( ok ) { //Ce triangle n'appartient � aucun autre des groupes, on lui cr�e un nouyeau groupe
          vector<vertex*> newV;
          newV.push_back(triangles[i]->moyenne());
          plan_detectes.push_back(newV);
          hauteur_detectes.push_back(triangles[i]->moyenne()->scalaire(axe1));

        }

        //cout<<"hello2"<<endl;
    }

    //cout<<"hello3"<<endl;
    for(unsigned int i= 0; i< hauteur_detectes.size(); i++ ) {
        plans.push_back(planEnglobantRectangulaire(plan_detectes[i], hauteur_detectes[i], axe1, axe2, axe3));
    }



}

double scene::calculerHauteurMoyenne( vector<vertex*> vecteur, vertex* axe) {
    double retour=0;

    for ( unsigned int i=0; i<vecteur.size(); i++ ) {
      retour += vecteur[i]->scalaire(axe);
    }
    retour = retour/vecteur.size();
    return retour;
}

plan* scene::planEnglobantRectangulaire(vector<vertex*> points, double posAxe1, vertex* axe1, vertex* axe2, vertex* axe3 ) {
    plan* retour = new plan; // On fait l'approximation que tous les points sont sur le m�me plan � peut pr�t, on va donc raisonner en 2D
    /*
        Dans le plan :
            P1 point y et z min
            P2 point y max et z min
            P3 point y min et z max
            P4 point y max et z max
    */
    double minY= points[0]->scalaire(axe2);
    double minZ= points[0]->scalaire(axe3);
    double maxY= points[0]->scalaire(axe2);
    double maxZ= points[0]->scalaire(axe3);
    //cout<<"Wesh1"<<endl;
    for ( unsigned int i=1; i<points.size(); i++) { //On parcours tous les points
        double coordY = points[i]->scalaire(axe2);
        double coordZ = points[i]->scalaire(axe3);
        if ( coordY < minY )
            minY = coordY;
        if ( coordZ < minZ )
            minZ = coordZ;
        if ( coordY > maxY )
            minY = coordY;
        if ( coordZ > maxZ )
            maxZ = coordZ;
    }

    //cout<<"Wesh2"<<endl;
    //retour->setP1(*axe1);
    //cout<<"Wesh3"<<endl;
    //if ( maxZ != nan)
    //cout<<maxZ * *axe2<<" "<<maxZ<<endl;
    vertex P1 = minY * *axe2 + minZ * *axe3;
    vertex P2 = maxY * *axe2 + minZ * *axe3;
    vertex p3 = minY * *axe2 + maxZ * *axe3;
    vertex P4 = maxY * *axe2 + maxZ * *axe3;
    cout<<P1<<P2<<P3<<P4;

    retour->setP1(posAxe1 * *axe1 + minY * *axe2 + minZ * *axe3);
    retour->setP2(posAxe1 * *axe1 + maxY * *axe2 + minZ * *axe3);
    retour->setP3(posAxe1 * *axe1 + minY * *axe2 + maxZ * *axe3);
    retour->setP4(posAxe1 * *axe1 + maxY * *axe2 + maxZ * *axe3);
    retour->setNbre_triangles(points.size());
    return retour;
}

void scene::filte() {
    double moy;
    for ( int i=0; i<plans.size(); i++ ) {
        moy += plans.size();
    }
    moy = ((float)moy)/plans.size();

    for ( int i=0; i<plans.size(); i++ ) {
        if ( plans[i]->getNbre_triangles() > moy)
            plans_filtred.push_back(plans[i]);

    }

}

void scene::writePlans() {
   //plans_filtred = plans;

  string fname;
  cout<<"Nom du fichier de sortie des plans :"<<endl;
  cin>>fname;
  if(fname.size() == 0) {
    fname = "plans.txt";
  } else if(fname.find(".txt", fname.size()-4)) {
    fname += ".txt";
  }
  ofstream myFile (fname.c_str(), ios::out | ios::binary);
  //myFile<<plans_filtred.size();
  //myFile<<" ";
  for ( int i=0; i<plans_filtred.size(); i++ ) {
    myFile<<plans_filtred[i]->getP1()->getX();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP1()->getY();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP1()->getZ();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP2()->getX();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP2()->getY();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP2()->getZ();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP3()->getX();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP3()->getY();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP3()->getZ();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP4()->getX();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP4()->getY();
    myFile<<" ";
    myFile<<plans_filtred[i]->getP4()->getZ();
    myFile<<" ";
  }
}
