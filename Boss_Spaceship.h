#ifndef _BOSS_SPACESHIP_H              // Prevent multiple definitions if this 
#define _BOSS_SPACESHIP_H                    // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "Spaceship.h"
#include "constants.h"
#include "shell.h"

namespace Boss_SpaceshipNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = BOSS_SPACESHIP_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = BOSS_SPACESHIP_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI / 4;				// spin at x radians per second
	const float SPEED = SPACESHIP_SPEED;						// X pixels per second
	const float MASS = SPACESHIP_MASS;							// mass
	const int   TEXTURE_COLS = BOSS_SPACESHIP_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = BOSS_SPACESHIP_START_FRAME;			//which frame to start
	const int   END_FRAME = BOSS_SPACESHIP_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = BOSS_SPACESHIP_ANIMATION_DELAY;   // time between frames
	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Boss_Spaceship : public Entity
{
private:
	bool isAlive = true;
	bool hasFiredWeapon = false; //may remove this, use this to check if spaceship has fired on player in the last X seconds
	int health=4;
	Shell shell;
	Image turret;
public:
	// constructor
	Boss_Spaceship();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	int getHealth(){ return health; }
	void setHealth(int hp){ health = hp; }


	//any other relevant methods here

};

#endif