#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace PlayerNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = PLAYER_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = PLAYER_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI / 4;				// spin at x radians per second
	const float MASS = PLAYER_MASS;							// mass
	const int   TEXTURE_COLS = PLAYER_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_LEFT_FRAME = PLAYER_LEFT_START_FRAME;			//which frame to start
	const int   END_LEFT_FRAME = PLAYER_LEFT_END_FRAME;				//which frame to end
	const int   START_RIGHT_FRAME = PLAYER_RIGHT_START_FRAME;			//which frame to start
	const int   END_RIGHT_FRAME = PLAYER_RIGHT_END_FRAME;
	const float ANIMATION_DELAY = PLAYER_ANIMATION_DELAY;   // time between frames
	const float BASE_STRENGTH = PLAYER_BASE_STRENGTH;

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Player : public Entity
{
private:
	
	float baseStrength;
	bool	isHoldingCannonball = false;

	bool	isAlive = true;
	float maxHealth;
	int health;
	float speed;						// X pixels per second

public:
	// constructor
	Player();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void setIsHoldingCannonball(bool isHeld)
	{
		isHoldingCannonball = isHeld;
	}

	//setters
	void setSpeed(float s);

	//getters
	float getSpeed();
};
#endif

