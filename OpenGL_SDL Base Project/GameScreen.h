#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
using std::string;

class Camera;

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OutputLine(float x, float y, string text);

protected:
	Camera* mCamera;
};


#endif //_GAMESCREEN_H