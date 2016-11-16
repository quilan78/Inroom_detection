#include "include.h"

int main() {
	string fichier;
	vector<triangle*> v;
	cout<<"Nom du fichier à insérer : "<<endl;
	cin>>fichier;
	unsigned long nbreTri = read_stl(fichier, v);
	cout<<nbreTri;
	return 0;
}
