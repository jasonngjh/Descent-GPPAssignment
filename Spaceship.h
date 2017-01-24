#ifndef _SPACESHIP_H                 // Prevent multiple definitions if this 
#define _SPACESHIP_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace SpaceshipNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = SPACESHIP_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = SPACESHIP_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI / 4;				// spin at x radians per second
	const float SPEED = SPACESHIP_SPEED;						// X pixels per second
	const float MASS = SPACESHIP_MASS;							// mass
	const int   TEXTURE_COLS = SPACESHIP_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = SPACESHIP_START_FRAME;			//which frame to start
	const int   END_FRAME = SPACESHIP_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = SPACESHIP_ANIMATION_DELAY;   // time between frames

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Spaceship : public Entity
{
private:

	bool isAlive = true;
	bool isAtCriticalHealth = false; 
	bool hasFiredWeapon = false; //may remove this, use this to check if spaceship has fired on player in the last X seconds
	int health; //counted in small numbers, represents amount of times spaceship can get hit again, maybe can use different animation frames to indicate damage

public:
	// constructor
	Spaceship();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	int getHealth(){ return health; }
	void setHealth(int hp){ health = hp; }

	bool getIsAlive(){ return isAlive; }
	void setIsAlive(bool lifeState){ isAlive = lifeState; }// isAlive = !isAlive

	bool getIsAtCriticalHealth() { return isAtCriticalHealth; }
	void setIsAtCritical(bool criticalState) { isAtCriticalHealth = criticalState; }



};
#endif

