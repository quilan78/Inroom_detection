class scene {

  private:
    vector<triangle*> v;
    vector<triangle*> proj_carre;
    void calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale);
    vertex* v1;
    vertex* v2;
    vertex* v3;
    //int getPlusGrandeComposante(vertex* v);


  public:
    unsigned long read_stl(string fname);
    vertex* getNormaleMaxixmum(float sensib);


};
