

void read_stl(string fname, vector<triangle*> &v){

    //!!
    //don't forget ios::binary
    //!!
    ifstream myFile ( fname.c_str(), ios::in | ios::binary);

    char header_info[80] = "";
    char nTriChar[4];
    unsigned long nTri;

    char trash[2];

    //read 80 byte header
    if (myFile) {
        myFile.read (header_info, 80);
        myfile.read(nTriChar, 4);
        nTri = static_cast<unsigned long>nTriChar;

        for ( int i=0; i<nTri; i++) {
            vertex normal;
            vertex p1;
            vertex p2;
            vertex p3;
            myfile.read(nTriChar, 12);
            myfile.read(p1, 12);
            myfile.read(p2, 12);
            myfile.read(p3, 12);
            v.push_back( new triangle(*p1, *p2, *p3, *normal));
            myfile.read(trash, 2);
        }
    }
}

