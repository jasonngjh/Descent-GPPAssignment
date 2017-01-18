#include "Cheese.h"

//=============================================================================
// default constructor
//=============================================================================
Cheese::Cheese() : Entity()
{
	spriteData.width = CheeseNS::WIDTH;           // size of Ship1
	spriteData.height = CheeseNS::HEIGHT;
	spriteData.x = CheeseNS::X;                   // location on screen
	spriteData.y = CheeseNS::Y;
	spriteData.rect.bottom = CheeseNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = CheeseNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = CheeseNS::ANIMATION_DELAY;
	startFrame = CheeseNS::START_FRAME;     // first frame of ship animation
	endFrame = CheeseNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = CheeseNS::WIDTH / 2.0;
	mass = CheeseNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Cheese::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Cheese::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Cheese::update(float frameTime)
{
	//if thrown
	spriteData.angle += frameTime * CheeseNS::ROTATION_RATE;
	if (spriteData.x > GAME_WIDTH - CheeseNS::WIDTH*getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - CheeseNS::WIDTH*getScale();
		velocity.x = -velocity.x;               // reverse X direction
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		velocity.x = -velocity.x;               // reverse X direction
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - CheeseNS::HEIGHT*getScale())
	{
		// position at bottom screen edge
		spriteData.y = GAME_HEIGHT - CheeseNS::HEIGHT*getScale();
		velocity.y = -velocity.y;               // reverse Y direction
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		spriteData.y = 0;                       // position at top screen edge
		velocity.y = -velocity.y;               // reverse Y direction
	}
}

//additional methods here
