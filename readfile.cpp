#include "include.h"

unsigned long read_stl(string fname, vector<triangle*> &v){

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
