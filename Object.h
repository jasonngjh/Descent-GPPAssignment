#ifndef _OBJECT_H                 // Prevent multiple definitions if this 
#define _OBJECT_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ObjectNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = OBJECT_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = OBJECT_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI / 4;				// spin at x radians per second
	const float SPEED = OBJECT_SPEED;						// X pixels per second
	const float MASS = OBJECT_MASS;							// mass
	const int   TEXTURE_COLS = OBJECT_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = OBJECT_START_FRAME;			//which frame to start
	const int   END_FRAME = OBJECT_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = OBJECT_ANIMATION_DELAY;   // time between frames


	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Object : public Entity
{
private:
	bool    shieldOn;
public:
	// constructor
	Object();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	//any other relevant methods here

};
#endif

