////////////////////////////////////////////////////////////////////////////

// Projet P1RV - David Tuckey, Armand Cadet

// Fichier main.cpp

///////////////////////////////////////////////////////////////////////////


#include "include.h"



int main() {
    string fichier = "nvx_mesh.stl"; // Fichier stl
    scene notreScene;
    cout<<"Nombre de triangles : "<<endl;

    unsigned long nbreTri = notreScene.read_stl(fichier); // On lit le fichier stl

    cout<<nbreTri<<endl; // Affichage du nombre de triangles

		int choix=0;
		cout<<"Quel algorithme voulez vous utiliser ? : 1=projection, 2=sans proj"<<endl;
		cin>>choix;
		if (choix == 1 ) { // algorithme numéro 1
				vertex* a = notreScene.createBase(0.01); // On génère la base adapté à la scène

				notreScene.projeterTriangles(); // On projète tous les triangles

				// Affichage du nombre de triangles dans chaque groupes
				cout<<notreScene.getProj_v1().size()<<endl;
				cout<<notreScene.getProj_v2().size()<<endl;
				cout<<notreScene.getProj_v3().size()<<endl;

				// On crée les plans pour chacunes des normales
			  notreScene.detectionPlanV1(0.5);
			  notreScene.detectionPlanV2(0.5);
			  notreScene.detectionPlanV3(0.5);

		}else if ( choix == 2 ) { //algorithme numéro 2
			notreScene.algoSansProjection(0.01, 0.5); // Algortihme numéro 2

		}

    notreScene.filtre(); // On filtre les plans générés
    notreScene.writePlans(); // On les écrit dans un fichier
    return 0;
}
