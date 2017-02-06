#ifndef _SPACESHIP_BULLET_H                 // Prevent multiple definitions if this 
#define _SPACESHIP_BULLET_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace Spaceship_bullet_NS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = SPACESHIP_BULLET_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = SPACESHIP_BULLET_HEIGHT;						// image height
	const int   TEXTURE_COLS = SPACESHIP_BULLET_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = SPACESHIP_BULLET_START_FRAME;			//which frame to start
	const int   END_FRAME = SPACESHIP_BULLET_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = SPACESHIP_BULLET_ANIMATION_DELAY;   // time between frames
	const int BULLET_DAMAGE = SPACESHIP_BULLET_DAMAGE;

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Spaceship_bullet : public Entity
{
private:

	bool	isAlive;
	float	speed = SPACESHIP_BULLET_SPEED;						// X pixels per second

public:
	// constructor
	Spaceship_bullet();

	int damage = SPACESHIP_BULLET_DAMAGE;

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void setSpeed(float s) { speed = s; }
	float getSpeed() { return speed; }

};
#endif

