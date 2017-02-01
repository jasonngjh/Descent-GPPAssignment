#include "powerup.h"
//=============================================================================
// default constructor
//=============================================================================
Powerup::Powerup() :Entity()
{
	spriteData.width = PowerupNS::WIDTH;           // size of Ship1
	spriteData.height = PowerupNS::HEIGHT;
	spriteData.x = PowerupNS::X;                   // location on screen
	spriteData.y = PowerupNS::Y;
	spriteData.rect.bottom = PowerupNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PowerupNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = PowerupNS::ANIMATION_DELAY;
	startFrame = PowerupNS::START_FRAME;     // first frame of ship animation
	endFrame = PowerupNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = PowerupNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Powerup::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//health = SPACESHIP_STARTING_HEALTH;

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Powerup::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Powerup::update(float frameTime)
{
	//shell.update(frameTime, turret);
	Entity::update(frameTime);
}

//additional methods here