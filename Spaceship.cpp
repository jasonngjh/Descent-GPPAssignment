#include "Spaceship.h"

//=============================================================================
// default constructor
//=============================================================================
Spaceship::Spaceship() : Entity()
{
	spriteData.width = SpaceshipNS::WIDTH;           // size of Ship1
	spriteData.height = SpaceshipNS::HEIGHT;
	spriteData.x = SpaceshipNS::X;                   // location on screen
	spriteData.y = SpaceshipNS::Y;
	spriteData.rect.bottom = SpaceshipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = SpaceshipNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = SpaceshipNS::ANIMATION_DELAY;
	startFrame = SpaceshipNS::START_FRAME;     // first frame of ship animation
	endFrame = SpaceshipNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = SpaceshipNS::WIDTH / 2.0;
	mass = SpaceshipNS::MASS;			
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Spaceship::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	health = SPACESHIP_STARTING_HEALTH;

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Spaceship::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Spaceship::update(float frameTime)
{
	Entity::update(frameTime);

	if (isAtCriticalHealth)
	{
		//may consider moving this to somewhere else, since it's something that needs to be only called once anyway
		startFrame = SPACESHIP_DAMAGED_START_FRAME;
		endFrame = SPACESHIP_DAMAGED_END_FRAME;
	}
		

}

//additional methods here
