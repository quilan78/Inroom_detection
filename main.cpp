#include "include.h"



int main() {
    string fichier = "example.stl";
    scene notreScene;
    cout<<"Nom du fichier à insérer : "<<endl;
    //cin>>fichier;
    unsigned long nbreTri = notreScene.read_stl(fichier);
    cout<<nbreTri<<endl;
	vertex* a = notreScene.getNormaleMaxixmum(0.001);
	//cout<<"("<<a->getX()<<","<<a->getY()<<","<<a->getZ()<<")"<<endl;
    return 0;
}
