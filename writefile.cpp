#include "include.h"

void write_stl(string fname, vector<triangle*> &v){

	ofstream myFile (fname.c_str(), ios::out | ios::app | ios::binary);
	for(int i = 0; i < 80; i++) {
		myFile << '\0';
	}
	unsigned long size = v.size();
	myFile << (char)(size & 0xFF) << (char)((size >> 8) & 0xFF) << (char)((size >> 16) & 0xFF) << (char)((size >> 24) & 0xFF);
	for(unsigned long i = 0; i < size; i++) {
		myFile  << v[i].getNorm() << v[i].getP1() << v[i].getP2() << v[i].getP3() << '\0' << '\0';
	}
}

