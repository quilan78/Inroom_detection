class scene {
	private:
		vector<triangle*> v;
		vector<triangle*> proj_carre;
		void scene::calculerMoyenneNormales( vector<triangle*> triangles, vertex* normale);

	public:
		unsigned long read_stl(string fname);
		vertex* getNormaleMaxixmum(float sensib);
}
