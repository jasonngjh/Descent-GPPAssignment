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
	shieldOn = false;
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
	
}

//additional methods here
