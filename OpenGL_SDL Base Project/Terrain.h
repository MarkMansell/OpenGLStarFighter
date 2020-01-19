#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../gl/glut.h"
#include "Constants.h"

class Terrain
{
//--------------------------------------------------------------------------------------------------
public:
	Terrain();
	~Terrain();

	bool		Initialise();
	void		Render();
	void		Update(float deltaTime);
	void		SetTexture(GLuint _ID);


//--------------------------------------------------------------------------------------------------
private:
	char textureName[20];
	GLuint _TextureID;
	GLubyte heightmap[TERRAIN_SIZE * TERRAIN_SIZE];
};

#endif //_TERRAIN_H