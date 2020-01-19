#include "GameScreen.h"
#include "../gl/glut.h"
#include "Camera.h"
#include "Constants.h"


//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen()
{
	float aAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float aNear = 0.1f;
	float aFar = 1000.0f;
	float aFieldOfView = 60.0f;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluPerspective(aFieldOfView, aAspect, aNear, aFar);
	
	//Set up the camera.
	mCamera = Camera::GetInstance();
	mCamera->SetAsPerspective( Vector3D(0.0f, 0.0f, 10.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f),
								aNear, aFar, aFieldOfView, aAspect );


	//OpenGL set up.
	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
	//Clear the screen.
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	mCamera->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	mCamera->Update(deltaTime, e);
}

void GameScreen::OutputLine(float x, float y, string text)
{	
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2d(x, y); //Location of text on screen
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}	
	glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------------------------