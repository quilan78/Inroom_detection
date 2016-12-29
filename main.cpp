#include "include.h"


int main() {
    string fichier = "nvx_mesh.stl";
    scene notreScene;
    cout<<"Nom du fichier à inserer : "<<endl;
    //cin>>fichier;
    unsigned long nbreTri = notreScene.read_stl(fichier);
    cout<<nbreTri<<endl;

		int choix=0;
		cout<<"Quel algorithme voulez vous utiliser ? : 1=projection, 2=sans proj"<<endl;
		cin>>choix;
		if (choix == 1 ) {
				vertex* a = notreScene.createBase(0.01);
				cout<<"1"<<endl;
				notreScene.projeterTriangles();
				cout<<"2"<<endl;
				//notreScene.write_stl("sortie.stl");

				cout<<notreScene.getProj_v1().size()<<endl;

				cout<<notreScene.getProj_v2().size()<<endl;
				cout<<notreScene.getProj_v3().size()<<endl;

			    notreScene.detectionPlanV1(0.5);
				cout<<"3"<<endl;
			    notreScene.detectionPlanV2(0.5);
				cout<<"4"<<endl;
			    notreScene.detectionPlanV3(0.5);
				cout<<"5"<<endl;

			    vector<plan*> plans = notreScene.getPlans();
			    int maxi = 0;
			    for ( int i=0; i<plans.size(); i++) {
			        cout<<"Plan numero : "<<i<<endl;
			        cout<<plans[i]->getP1()<<endl;
			        cout<<plans[i]->getP2()<<endl;
			        cout<<plans[i]->getP3()<<endl;
			        cout<<plans[i]->getP4()<<endl;
			        cout<<"Nbre de triangles : "<<plans[i]->getNbre_triangles()<<endl;
			        if (plans[i]->getNbre_triangles() > maxi  )
			            maxi = plans[i]->getNbre_triangles();
			        cout<<endl<<endl;
			    }
			    cout<<maxi<<endl;

		}else if ( choix == 2 ) {
			notreScene.algoSansProjection(0.01, 0.5);

		}

    notreScene.filtre();
    notreScene.writePlans();
	//cout<<"("<<a->getX()<<","<<a->getY()<<","<<a->getZ()<<")"<<endl;
    return 0;
}

