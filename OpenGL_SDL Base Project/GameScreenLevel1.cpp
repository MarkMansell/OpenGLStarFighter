#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include "Constants.h"
#include "Commons.h"
#include "Camera.h"
#include "Texture.h"


using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	// Initialize all the scene objects
	mTerrain.Initialise();

	// ---------------------------------------------------------------Initiate the models-----------------------------------------------
		
	m_p3DSModel = new object3DS(Vector3D(0.0f, -1.0f, -10.0f), "Objects/Octopus.3ds"); // Create the Octopus

	m_SpaceshipBase = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Spaceship1.3ds"); // Create the Spaceship

	m_Wing[0] = new object3DS(Vector3D(6.1f, 2.4f, 0.3f), "Objects/Wing.3ds"); // Left wings
	m_Wing[1] = new object3DS(Vector3D(6.1f, 2.4f, 0.3f), "Objects/Wing.3ds");
	m_Wing[2] = new object3DS(Vector3D(-6.1f, 2.4f, 0.3f), "Objects/Wing.3ds"); // Right wings
	m_Wing[3] = new object3DS(Vector3D(-6.1f, 2.4f, 0.3f), "Objects/Wing.3ds");

	m_R2D2Head = new object3DS(Vector3D(3.5f, 1.0f, 0.3f), "Objects/R2D2_Head.3ds"); // R2D2's head SWAP TO NEW OBJECT

	m_Stars[0] = new object3DS(Vector3D(1.0f, 0.0f, 0.5f), "Objects/Star.3ds"); // Create Stars (first side)
	m_Stars[1] = new object3DS(Vector3D(0.5f, 0.0f, 0.1f), "Objects/Star.3ds");
	m_Stars[2] = new object3DS(Vector3D(-0.5f, 0.0f, -0.1f), "Objects/Star.3ds");	
	m_Stars[3] = new object3DS(Vector3D(-1.0f, 0.0f, 0.5f), "Objects/Star.3ds"); // Create Stars (second side)

	m_Booster = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/Booster.3ds"); // Create the booster

	m_LandingGear = new object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Objects/LandingGear.3ds"); // Create the Landing Gear

	m_OBJCube = new OBJLoader("Objects/OBJCube1.obj");
	m_LandingGear->SetRotation(90.0f, 1.0f, 0.0f, 0.0f);

	SelectedObject = m_Booster; // Set initial selected object

	// ---------------------------------------------------------------Textures for the models-----------------------------------------------
	glEnable(GL_TEXTURE_2D);
	Texture2D* SpaceshipTex = new Texture2D(); // Spaceship Texuture
	SpaceshipTex->Load("Textures/Spaceship_UV.raw", 512, 512);
	m_SpaceshipBase->SetTexture(SpaceshipTex->GetID());

	
	Texture2D* R2D2HeadTex = new Texture2D(); // R2D2's Head Texture
	R2D2HeadTex->Load("Textures/R2D2_UV.raw", 512, 512);
	m_R2D2Head->SetTexture(R2D2HeadTex->GetID());
	m_OBJCube->SetTexture(R2D2HeadTex->GetID());

	Texture2D* PenguinTex = new Texture2D(); // Penguin Texture	
	PenguinTex->Load("Textures/Penguins.raw", 512, 512);
	m_p3DSModel->SetTexture(PenguinTex->GetID());
	
	Texture2D* WingTex = new Texture2D(); // Wing Texture
	WingTex->Load("Textures/Wing_UV.raw", 512, 512);
	for (size_t i = 0; i < (sizeof(m_Wing - 1));)
	{
		m_Wing[i]->SetTexture(WingTex->GetID());
		i++;
	}

	Texture2D* StarsTex = new Texture2D(); // Wing Texture
	StarsTex->Load("Textures/Star_UV.raw", 512, 512);
	for (size_t i = 0; i < (sizeof(m_Stars - 1));)
	{
		m_Stars[i]->SetTexture(StarsTex->GetID());
		i++;
	}

	Texture2D* BoosterTex = new Texture2D();
	BoosterTex->Load("Textures/Booster_UV.raw", 512, 512);
	m_Booster->SetTexture(BoosterTex->GetID());
	booster1 = BoosterTex->GetID();

	Texture2D* BoosterTex2 = new Texture2D();
	BoosterTex2->Load("Textures/Booster1_UV.raw", 512, 512);
	booster2 = BoosterTex2->GetID();

	Texture2D* LandingGearTex = new Texture2D();
	LandingGearTex->Load("Textures/LandingGear_UV.raw", 512, 512);
	m_LandingGear->SetTexture(LandingGearTex->GetID());

	Texture2D* TerrainTex = new Texture2D();
	TerrainTex->Load("Textures/Moon_UV.raw", 512, 512);
	mTerrain.SetTexture(TerrainTex->GetID());

	Texture2D* NightStarTex = new Texture2D();
	NightStarTex->Load("Textures/NightStars_UV.raw", 1024, 1024);
	m_OBJCube->SetTexture(NightStarTex->GetID());

	
	// ---------------------------------------------------------------Rotations for the models-----------------------------------------------

	// Initial Rotations	
	m_Wing[2]->SetRotation(180.0f, 0.0f, 1.0f, 0.0f); // Right wing
	m_Wing[3]->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);

	
	// ---------------------------------------------------------------Setting the start values-----------------------------------------------
	wingAngle = 0.0f;
	DeployWings = false;
	wingsUp = false; // not in use
	wingButtonPressed = false; // Check whether the wing button has been pushed

	HeadAngle = 0.0f,
	SpinHead = false;

	StarAngle1 = 0.0f;
	LGearAngle = 0.0f;
	BoosterAngle = 0.0f;

	ObjectButton = false;
	Objectindex = 1;
	DeployGear = false;

	JetAngle = 0.0f;

	//---------------------------------------------------------------Set up the HUD-----------------------------------------------
	WingState = "Wings Closed";
	Headstate = "Stopped";
	txtObject = "Boosters";
	txtLandingGear = "Up";
	
}



//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Parent class deals with camera.
	GameScreen::Render();

	glPushMatrix();
		glTranslatef(0.0f, -3.0f, 0.0f);
		mTerrain.Render();	//Draw the terrain.
	glPopMatrix();
	

	glPushMatrix(); // Render the sky box
		glDisable(GL_CULL_FACE);
		m_OBJCube->Render();
		glEnable(GL_CULL_FACE);
	glPopMatrix();


	glPushMatrix(); // Octopus Matrix
	//m_p3DSModel->render();
	glPopMatrix();

	
	glPushMatrix(); // ---------------------------------Parent Spaceship Matrix-----------------------------------------------

		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);		
		glRotatef(JetAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -7.0f, 4.0f);

		m_SpaceshipBase->SetRotation(90.f, 1.0f, 0.0f, 0.0f);	
		m_SpaceshipBase->render();
	
	glPushMatrix(); // // ---------------------------------Landing Gear Matrix-----------------------------------------------
		glTranslatef(0.0f, -7.0f, -0.5f);
		m_LandingGear->render();
	glPopMatrix();

	glPushMatrix(); // Back gear matrix
		glTranslatef(1.0f, 4.0f, -0.5f);
		m_LandingGear->render();
	glPopMatrix();

	glPushMatrix(); // Back gear matrix
		glTranslatef(-1.0f, 4.0f, -0.5f);
		m_LandingGear->render();
	glPopMatrix();

	glPushMatrix(); // ---------------------------------Booster Matrix-----------------------------------------------
		glTranslatef(0.7f, 5.5f, 0.2f);
		m_Booster->render();
	glPopMatrix();

	glPushMatrix(); // Render second booster
		glTranslatef(-0.7f, 5.5f, 0.2f);
		m_Booster->render();
	glPopMatrix();
	
	// --------------------------------------------------Wings Matrix-----------------------------------------------
	glPushMatrix(); // Wing 1 matrix
		m_Wing[0]->render();
	glPopMatrix();

	glPushMatrix(); // Wing 2 matrix
		m_Wing[1]->render();
	glPopMatrix();

	glPushMatrix(); // Wing 3 matrix
		m_Wing[2]->render();
	glPopMatrix();

	glPushMatrix(); // Wing 4 matrix
		m_Wing[3]->render();
	glPopMatrix();

	glPushMatrix(); // ---------------------------------R2D2 Head and Stars Matrix-----------------------------------------------

		glPushMatrix();
			TempVector = m_R2D2Head->GetStartPos(); // Store Head temporarily
			glTranslatef(TempVector.x, TempVector.y, TempVector.z);
			glRotatef(StarAngle1, 0.0f, 0.0f, 1.0f);		
			m_Stars[0]->render(); // First Star
			glScalef(0.5f, 0.5f, 0.5f);
			glRotatef(StarAngle1 + 0.4f, 0.0f, 0.0f, 1.0f);
			m_Stars[1]->render(); // Set star relative to first star
			TempVector = m_Stars[1]->GetStartPos();
			glTranslatef(-TempVector.x, -TempVector.y, -TempVector.z); // Minus original movement
			m_Stars[2]->render();			
		glPopMatrix();

		glPushMatrix();
			TempVector = m_R2D2Head->GetStartPos(); // Store Head temporarily
			glTranslatef(TempVector.x, TempVector.y, TempVector.z);
			glRotatef(StarAngle1, 0.0f, 0.0f, 1.0f);
			m_Stars[3]->render(); // Second Star
			glScalef(0.5f, 0.5f, 0.5f);
			glRotatef(StarAngle1 + 0.4f, 0.0f, 0.0f, 1.0f);
			m_Stars[1]->render(); // Set star relative to first star
			TempVector = m_Stars[1]->GetStartPos();
			glTranslatef(-TempVector.x, -TempVector.y, -TempVector.z); // Minus original movement
			m_Stars[2]->render();
		glPopMatrix();


	m_R2D2Head->render();	
	glPopMatrix();
	
	
	glPopMatrix(); // ---------------------------------End of Matrix-----------------------------------------------
	

	//Start Hud
	OutputLine(SCREEN_WIDTH / 2 - 20, 450, "Star Fighter"); // Title of the game
	OutputLine(30, 420, "Object Selected: " + txtObject); // Show the state of the wings
	OutputLine(30, 405, "Wings: " + WingState); // Show the state of the wings		
	OutputLine(30, 390, "R2D2's Head: " + Headstate); // Say whether the head is spinning
	OutputLine(30, 375, "Landing Gear: " + txtLandingGear);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	GameScreen::Update(deltaTime, e);
	mCurrentTime += deltaTime;

	if (GetKeyState('Z') & 0x8000)
	{
		JetAngle -= deltaTime + 0.3;
	}

	if (GetKeyState('X') & 0x8000)
	{
		JetAngle += deltaTime + 0.3;
	}


	m_Stars[0]->SetRotation(StarAngle1, 0.0f, 0.0f, 1.0f);
	m_Stars[3]->SetRotation(StarAngle1 * 0.5f, 0.0f, 0.0f, 1.0f);
	StarAngle1 += deltaTime + 0.6f;

	// -----------------------------------------------Swap Objects-----------------------------------------------
	if (GetKeyState('1') & 0x8000)
	{
		txtObject = "Boosters";
		SelectedObject = m_Booster;
		Objectindex = 1;
	}
	if (GetKeyState('2') & 0x8000)
	{	
		txtObject = "Landing Gear";
		SelectedObject = m_LandingGear;
		Objectindex = 2;
	}
	// ---------------------------------F key Pushed = Landing Gear-----------------------------------------------
	if (GetKeyState('F') & 0x8001)
	{
		if (ObjectButton == true && Objectindex == 2) // Booster
		{		
			DeployGear = true;
			ObjectButton = false;
			txtLandingGear = "Down";
		}

	}
	else
	{
		if (ObjectButton == false && Objectindex == 2) // Booster
		{
			DeployGear = false;
			ObjectButton = true;
			txtLandingGear = "Up";
		}

	}
	// ---------------------------------F key Pushed = Booster-----------------------------------------------
	if (GetKeyState('F') & 0x8000)
	{
		if (Objectindex == 1)
		{
			//Rotate booster
			SelectedObject->SetRotation(BoosterAngle, 0.0f, 1.0f, 0.0f);
			BoosterAngle += deltaTime + 1.0;
			m_Booster->SetTexture(booster2);
			m_SpaceshipBase->SetTransform(0.0f, 0.0f, -BoosterAngle * 0.2);
			
		}
	}
	else
	{
		m_Booster->SetTexture(booster1);
	}

	// ---------------------------------Deploying the Landing Gear-----------------------------------------------
	if (DeployGear == true)
	{
		if (Objectindex == 2)
		{
			if (LGearAngle <= 90.0f)
			{
				SelectedObject->SetRotation(-LGearAngle + 90.0f, 1.0f, 0.0f, 0.f); // working
				LGearAngle += deltaTime + 0.5f;
			}
		}

	}
	if (DeployGear == false)
	{
		if (Objectindex == 2)
		{
			if (LGearAngle >= 0.0f)
			{
				SelectedObject->SetRotation(-LGearAngle + 90.0f, 1.0f, 0.0f, 0.f);
				LGearAngle -= deltaTime + 0.5f;
			}
		}

	}
	// ---------------------------------Spin R2D2's Head-----------------------------------------------
	if (GetKeyState('T') & 0x8001)
	{
		SpinHead = true;
		Headstate = "Spinning";
	}
	else
	{
		SpinHead = false;
		Headstate = "Stopped";
	}

	if (SpinHead == true)
	{
		m_R2D2Head->SetRotation(HeadAngle, 0.0f, 0.0f, 1.0f);
		HeadAngle += deltaTime + 0.5f;
	}

	// ---------------------------------Deploying the Wings Button-----------------------------------------------
	if (GetKeyState('R') & 0x8001)
	{
		if (wingButtonPressed == true)
		{
			DeployWings = true;
			OutputDebugString("Open Wing 8001\n"); // Once i have pushed once
			WingState = "Open";
			wingButtonPressed = false;
			//m_Stars[0]->SetTransform(0.5f, 0.0f, 0.5f);
		}

	}
	else
	{
		if (wingButtonPressed == false)
		{
			DeployWings = false;
			OutputDebugString("Close Wing 8001\n"); // Once i have pushed once
			WingState = "Closed";
			wingButtonPressed = true;
		}

	}

	// ---------------------------------Deploying the Wings-----------------------------------------------
	if (DeployWings == true)
	{
		if (wingAngle <= 60.0f)
		{
			m_Wing[0]->SetRotation(wingAngle, 0.0f, 1.0f, 0.0f);
			m_Wing[1]->SetRotation(-wingAngle, 0.0f, 1.0f, 0.0f);

			m_Wing[2]->SetRotation(wingAngle + 180, 0.0f, 1.0f, 0.0f);
			m_Wing[3]->SetRotation(-wingAngle + 180, 0.0f, 1.0f, 0.0f);
			wingAngle += deltaTime + 0.1f;
		}	
	}	
	if (DeployWings == false)
	{
		if (wingAngle >= 0.0f)
		{
			m_Wing[0]->SetRotation(wingAngle, 0.0f, 1.0f, 0.0f);
			m_Wing[1]->SetRotation(-wingAngle, 0.0f, 1.0f, 0.0f);

			m_Wing[2]->SetRotation(wingAngle + 180, 0.0f, 1.0f, 0.0f);
			m_Wing[3]->SetRotation(-wingAngle + 180, 0.0f, 1.0f, 0.0f);
			wingAngle -= deltaTime + 0.1f;
		}
	}


}

//--------------------------------------------------------------------------------------------------