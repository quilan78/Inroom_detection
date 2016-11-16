#include "include.h"



int main() {
    string fichier = "fichier1.stl";
    scene notreScene;
    cout<<"Nom du fichier à insérer : "<<endl;
    //cin>>fichier;
    unsigned long nbreTri = notreScene.read_stl(fichier);
    cout<<nbreTri<<endl;
	cout<<notreScene.getNormaleMaxixmum(0.1);

    return 0;
}
