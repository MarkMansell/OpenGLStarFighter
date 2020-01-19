#include "Commons.h"
#include <string>
#include <Windows.h>
#include <gl/GLU.h>
using std::string;

class OBJLoader
{
public:
	OBJLoader(string modelFileName);
	~OBJLoader();


	bool LoadOBJ(obj_type_ptr obb, char *p_filename);
	void SetTexture(GLint _ID);
	void Render();

private:
	GLuint _TextureID;

	char fileName[20]; // Name of the file being opened


	int numVertices;
	int numUvs;
	int numNormals;
	int numPolygon;

	obj_type object;
	

};

