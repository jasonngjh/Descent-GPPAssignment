#include "object.h"

//=============================================================================
// default constructor
//=============================================================================
Object::Object() : Entity()
{
	spriteData.width = ObjectNS::WIDTH;           // size of Ship1
	spriteData.height = ObjectNS::HEIGHT;
	spriteData.x = ObjectNS::X;                   // location on screen
	spriteData.y = ObjectNS::Y;
	spriteData.rect.bottom = ObjectNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ObjectNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = ObjectNS::ANIMATION_DELAY;
	startFrame = ObjectNS::START_FRAME;     // first frame of ship animation
	endFrame = ObjectNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = ObjectNS::WIDTH / 2.0;
	shieldOn = false;
	mass = ObjectNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Object::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Object::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Object::update(float frameTime)
{
	
}

//additional methods here
