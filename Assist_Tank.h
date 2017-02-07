#ifndef _ASSIST_TANK_H                 // Prevent multiple definitions if this 
#define _ASSIST_TANK_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace Assist_Tank_NS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = ASSIST_TANK_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = ASSIST_TANK_HEIGHT;						// image height
	const int   TEXTURE_COLS = ASSIST_TANK_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = ASSIST_TANK_START_FRAME;			//which frame to start
	const int   END_FRAME = ASSIST_TANK_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = ASSIST_TANK_ANIMATION_DELAY;   // time between frames

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Assist_Tank : public Entity
{
private:

	bool	isAlive;
	float speed;						// X pixels per second

public:
	// constructor
	Assist_Tank();

	bool	isMovingRight;			//if false means is moving left

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void setSpeed(float s) { speed = s; }
	float getSpeed() { return speed; }

};
#endif

