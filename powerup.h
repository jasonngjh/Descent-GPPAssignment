#ifndef _POWERUP_H                 // Prevent multiple definitions if this 
#define _POWERUP_H                    // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <ctime>
#include <time.h>
#include <thread>
#include <future>
#include <iostream>

namespace PowerupNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = POWERUP_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = POWERUP_HEIGHT;						// image height
	const float ROTATION_RATE = POWERUP_ROTATION_RATE;		// spin at x radians per second
	const int   TEXTURE_COLS = POWERUP_TEXTURE_COLUMNS;     // texture has x columns
	const int   START_FRAME = POWERUP_START_FRAME;			//which frame to start
	const int   END_FRAME = POWERUP_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = POWERUP_ANIMATION_DELAY;  // time between frames


	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Powerup : public Entity
{
private:
	bool		shieldOn;
	int			playerNumber;		//which player is holding the Cannonball
	double		secondsPassed;
	int			powerupCode;
public:
	// constructor
	Powerup();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void beginExpireCountdown();
	void powerup_timer_start();

	double getSecondsPassed() { return secondsPassed; }						//for expiry timer
	void setSecondsPassed(double seconds) { secondsPassed = seconds; }		//for expiry timer

	int getPowerupCode() { return powerupCode; }			//retrieves the powerup code to reference effect in main program
	void setPowerupCode(int code) { powerupCode = code; }	//binds the powerup code to the powerup object for effect referencing in main program

};
#endif

