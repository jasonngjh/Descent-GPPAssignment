#ifndef _CHEESE_H                 // Prevent multiple definitions if this 
#define _CHEESE_H                     // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "player.h"

namespace CheeseNS
{

	//PERMANENT VALUES, ANYTHING YOU DECLARE HERE IS NOT MEANT TO BE MANIPULATED DURING THE GAME

	const int WIDTH = CHEESE_WIDTH;							//IMAGE WIDTH            
	const int HEIGHT = CHEESE_HEIGHT;						// image height
	const float ROTATION_RATE = (float)PI;				// spin at x radians per second
	const float BASE_SPEED = CHEESE_BASE_SPEED;						// X pixels per second
	const float MASS = CHEESE_MASS;							// mass
	const int   TEXTURE_COLS = CHEESE_TEXTURE_COLUMNS;      // texture has x columns
	const int   START_FRAME = CHEESE_START_FRAME;			//which frame to start
	const int   END_FRAME = CHEESE_END_FRAME;				//which frame to end
	const float ANIMATION_DELAY = CHEESE_ANIMATION_DELAY;   // time between frames
	

	//DERIVED PERMANENT VALUES
	const int X = GAME_WIDTH / 2 - WIDTH / 2;				// location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

}

// inherits from Entity class
class Cheese : public Entity
{
private:
	bool    shieldOn;
	int		playerNumber;		//which player is holding the cheese
public:
	// constructor
	Cheese();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void setCheeseIsHeld(int playerNo)
	{

		if (playerNumber == 1 || playerNumber == 2)
			playerNumber = playerNo;
		else
			playerNumber = 0;
		
	}
		

	//any other relevant methods here

};
#endif

