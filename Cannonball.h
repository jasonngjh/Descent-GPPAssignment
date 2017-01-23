//this class refers to the player projectile, change file name when necessary

#ifndef _CANNONBALL_H                 // Prevent multiple definitions if this 
#define _CANNONBALL_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace CannonballNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = CANNONBALL_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = CANNONBALL_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI;				// spin at x radians per second
	const float BASE_SPEED = CANNONBALL_BASE_SPEED;						// X pixels per second
	const float MASS = CANNONBALL_MASS;							// mass
	const int   TEXTURE_COLS = CANNONBALL_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = CANNONBALL_START_FRAME;			//which frame to start
	const int   END_FRAME = CANNONBALL_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = CANNONBALL_ANIMATION_DELAY;   // time between frames

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = 0;
		//GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Cannonball : public Entity
{
private:
	bool    shieldOn;
	int		playerNumber;		//which player is holding the Cannonball
	float acc = 9.8;
	float dt = 0.1; 
	
public:
	// constructor
	Cannonball();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void setCannonballIsHeld(int playerNo)
	{

		if (playerNumber == 1 || playerNumber == 2)
			playerNumber = playerNo;
		else
			playerNumber = 0;
		
	}
		
	enum hitWho{player, bossShip,spaceship};
	//any other relevant methods here

};
#endif

