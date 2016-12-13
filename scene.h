#pragma once
#include "include.h"
class scene {

  private:
    vector<triangle*> v;
    vector<triangle*> proj_v1;
    vector<triangle*> proj_v2;
    vector<triangle*> proj_v3;
    vector<plan*> plans;
    vector<plan*> plans_filtred;
    void calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale);
    vertex* v1;
    vertex* v2;
    vertex* v3;
    int getPlusGrandeComposante(vertex* v);
    void detectionPlan(double sensib, vector<triangle*>triangles, vertex* axe1, vertex* axe2, vertex* axe3 );
    double calculerHauteurMoyenne( vector<vertex*> vecteur, vertex* axe);
    plan* planEnglobantRectangulaire(vector<vertex*> points, double posAxe1, vertex* axe1, vertex* axe2, vertex* axe3 );
  public:
    unsigned long read_stl(string fname);
    void write_stl(string fname);
    vertex* createBase(float sensib);
    void projeterTriangles();
    void detectionPlanV1(double sensib);
    void detectionPlanV2(double sensib);
    void detectionPlanV3(double sensib);
    void writePlans();
    void filtre();
     vector<plan*>  getPlans() { return plans; }
     vector<triangle*>  getProj_v1() { return proj_v1; }
     vector<triangle*>  getProj_v2() { return proj_v2; }
     vector<triangle*>  getProj_v3() { return proj_v3; }

};
