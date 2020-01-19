#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Terrain.h"
#include "Commons.h"
#include "object3DS.h"
#include <Windows.h>
#include <gl/GLU.h>
#include "OBJLoader.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

//--------------------------------------------------------------------------------------------------
private:	
	float   mCurrentTime;

	Terrain mTerrain;

	object3DS* m_p3DSModel;
	object3DS* m_SpaceshipBase;
	object3DS* m_SpaceshipBase1;
	object3DS* m_Wing[4];
	object3DS* m_R2D2Head; //R2D2 Head 
	object3DS* m_Stars[6]; //Starts to orbit R2D2
	object3DS* m_Booster;
	object3DS* m_LandingGear;

	OBJLoader* m_OBJCube;

	object3DS* SelectedObject;

	Vector3D TempVector;

	bool DeployWings;
	bool wingsUp;
	bool wingButtonPressed;
	bool SpinHead;

	float wingAngle;
	float HeadAngle;
	float JetAngle;

	float StarAngle1;
	float LGearAngle;
	bool DeployGear;
	float BoosterAngle;

	string Headstate;
	string WingState;
	string txtObject;
	string txtLandingGear;

	GLint booster1;
	GLint booster2;

	int Objectindex;
	bool ObjectButton;

};


#endif //_GAMESCREENLEVEL1_H