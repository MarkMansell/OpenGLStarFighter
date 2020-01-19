#pragma once
//3DS Max Object type Details
#define MAX_VERTICES 15000
#define MAX_POLYGONS 15000

//Our vertex type
typedef struct
{
	float x, y, z;
} vertex_type;

//The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct
{
	int a, b, c;
} polygon_type;

//The mapcoord type, 2 texture coordinates for each vertex
typedef struct
{
	float u, v;
} mapcoord_type;

typedef struct
{
	int a, b, c;
} UV_index;

//The object type
typedef struct 
{
	char name[20];

	int vertice_qty;
	int polygons_qty;

	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];
	UV_index UV_Index[MAX_POLYGONS];
	int id_texture;
}obj_type, *obj_type_ptr;


enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(float initialX, float initialY, float initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}
};

typedef enum CameraType 
{
	CAMERA_PERSPECTIVE,
	CAMERA_ORTHO
};

typedef enum BufferType 
{
	BUFFER_SINGLE,
	BUFFER_DOUBLE
};

