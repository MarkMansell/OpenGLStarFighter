#include "OBJLoader.h"
#include <stdio.h>
#include <Windows.h>
#include "../gl/glut.h"

OBJLoader::OBJLoader(string modelFileName)
{
	numVertices = 0;
	numUvs = 0;
	numNormals = 1;
	numPolygon = 0;

	std::strcpy(fileName, modelFileName.c_str()); // copy the file name to char
	LoadOBJ(&object, fileName);
	_TextureID = NULL;
}

OBJLoader::~OBJLoader()
{
}

void OBJLoader::SetTexture(GLint _ID)
{
	_TextureID = _ID;
}
bool OBJLoader::LoadOBJ(obj_type_ptr p_object, char *p_filename)
{
	FILE * file = fopen(p_filename, "r");
	if (file == NULL)
	{
		printf("File Could not be opened. \n");
		return false;
	}
	while (1)
	{
		char LineHeader[128];
		//read the first word of the line
		int res = fscanf(file, "%s", LineHeader);
		if (res == EOF)
		{
			break; // EOF = End of file. Quit Loop
		}
		if (strcmp(LineHeader, "v") == 0)
		{
			Vector3D vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			p_object->vertex[numVertices].x = vertex.x;
			p_object->vertex[numVertices].y = vertex.y;
			p_object->vertex[numVertices].z = vertex.z;

			//printf("%f", vertex.x);
			//printf("%f", vertex.y);
			//printf("%f \n", vertex.z);
			numVertices++;
		}
		else if (strcmp(LineHeader, "vt") == 0)
		{
			Vector2D UV;
			fscanf(file, "%f %f\n", &UV.x, &UV.y);
			p_object->mapcoord[numUvs].u = UV.x;
			p_object->mapcoord[numUvs].v = UV.y;
			numUvs++;
		}
		else if (strcmp(LineHeader, "vn") == 0)
		{
			Vector3D normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
		}
		else if (strcmp(LineHeader, "f") == 0)
		{
			//std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			p_object->polygon[numPolygon].a = vertexIndex[0] - 1;
			p_object->polygon[numPolygon].b = vertexIndex[1] - 1;
			p_object->polygon[numPolygon].c = vertexIndex[2] - 1;

			p_object->UV_Index[numPolygon].a = uvIndex[0] -1;
			p_object->UV_Index[numPolygon].b = uvIndex[1] -1;
			p_object->UV_Index[numPolygon].c = uvIndex[2] -1;
			numPolygon++;
			
	/*		uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);*/
		}
	}

}

void OBJLoader::Render()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, _TextureID); // We set the active texture


	glBegin(GL_TRIANGLES); //glBegin and glEnd delimit the vertices that define a primative (in our case triangles)
	for (int l_index = 0; l_index < numPolygon; l_index++)
	{
		//FIRST VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.UV_Index[l_index].a].u, object.mapcoord[object.UV_Index[l_index].a].v);
		//Coordinates of the first vertex
		glVertex3f(object.vertex[object.polygon[l_index].a].x, object.vertex[object.polygon[l_index].a].y, object.vertex[object.polygon[l_index].a].z);
		//printf(" First Vertex %i ", l_index);
		//printf(" %f", object.vertex[object.polygon[l_index].a].x);
		//printf(" %f", object.vertex[object.polygon[l_index].a].y);	
		//printf(" %f \n", object.vertex[object.polygon[l_index].a].z);
		
		//SECOND VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.UV_Index[l_index].b].u, object.mapcoord[object.UV_Index[l_index].b].v);
		//Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].b].x, object.vertex[object.polygon[l_index].b].y, object.vertex[object.polygon[l_index].b].z);
		//printf(" 2nd vertex %i ", l_index);
		//printf(" %f", object.vertex[object.polygon[l_index].b].x);
		//printf(" %f", object.vertex[object.polygon[l_index].b].y);
		//printf(" %f \n", object.vertex[object.polygon[l_index].b].z);
		//THIRD VERTEX
		//Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.UV_Index[l_index].c].u, object.mapcoord[object.UV_Index[l_index].c].v);
		//Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].c].x, object.vertex[object.polygon[l_index].c].y, object.vertex[object.polygon[l_index].c].z);
		//printf(" 3nd vertex %i ", l_index);
		//printf(" %f", object.vertex[object.polygon[l_index].c].x);
		//printf(" %f", object.vertex[object.polygon[l_index].c].y);
		//printf(" %f \n", object.vertex[object.polygon[l_index].c].z);
	}

	glEnd();
	//glPopMatrix();
	glPolygonMode(GL_FRONT, GL_LINE);
}
