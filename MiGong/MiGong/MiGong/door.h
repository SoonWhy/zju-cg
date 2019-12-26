#ifndef door_h
#define door_h
#include <iostream>
#include <vector>
using namespace std;


class obj3dmodel {
	struct vertex {
		double x, y, z;
	};
	struct face {
		unsigned int v1, v2, v3;
		unsigned int t1, t2, t3;
	};
	struct texture {
		double x, y;
	};
	vector<vertex>vertexs;
	vector<face>faces;
	vector<texture>textures;
	int countf = 0;

public:
	GLuint tex;
	void parse(const char *filename);
	void draw();
	GLuint load_texture_obj(const char* file_name);
};


#endif