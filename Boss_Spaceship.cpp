#include "Boss_Spaceship.h"
//=============================================================================
// default constructor
//=============================================================================
Boss_Spaceship::Boss_Spaceship() :Entity()
{
	spriteData.width = Boss_SpaceshipNS::WIDTH;           // size of Ship1
	spriteData.height = Boss_SpaceshipNS::HEIGHT;
	spriteData.x = Boss_SpaceshipNS::X;                   // location on screen
	spriteData.y = Boss_SpaceshipNS::Y;
	spriteData.rect.bottom = Boss_SpaceshipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Boss_SpaceshipNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = Boss_SpaceshipNS::ANIMATION_DELAY;
	startFrame = Boss_SpaceshipNS::START_FRAME;     // first frame of ship animation
	endFrame = Boss_SpaceshipNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = Boss_SpaceshipNS::WIDTH / 2.0;
	mass = Boss_SpaceshipNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Boss_Spaceship::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	health = SPACESHIP_STARTING_HEALTH;

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Boss_Spaceship::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Boss_Spaceship::update(float frameTime)
{
	//shell.update(frameTime, turret);
	Entity::update(frameTime);
}

//additional methods here