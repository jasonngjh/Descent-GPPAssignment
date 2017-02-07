#include "Assist_Tank.h"

//=============================================================================
// default constructor
//=============================================================================
Assist_Tank::Assist_Tank() : Entity()
{
	spriteData.width = Assist_Tank_NS::WIDTH;           // size of Ship1
	spriteData.height = Assist_Tank_NS::HEIGHT;
	spriteData.x = Assist_Tank_NS::X;                   // location on screen
	spriteData.y = Assist_Tank_NS::Y;
	spriteData.rect.bottom = Assist_Tank_NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Assist_Tank_NS::WIDTH;
	frameDelay = Assist_Tank_NS::ANIMATION_DELAY;
	startFrame = Assist_Tank_NS::START_FRAME;     // first frame of ship animation
	endFrame = Assist_Tank_NS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::CIRCLE;
	speed = ASSIST_TANK_MOVEMENT_SPEED;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Assist_Tank::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	
	isMovingRight = true;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Assist_Tank::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Assist_Tank::update(float frameTime)
{

	Entity::update(frameTime);
	//moves the tank left and right
	if (isMovingRight)
	{

		if (spriteData.x + ASSIST_TANK_WIDTH < GAME_WIDTH)
			spriteData.x += frameTime * ASSIST_TANK_MOVEMENT_SPEED;
		else   //tank is at edge of screen
			isMovingRight = false;
	}

	if (!isMovingRight)
	{
		if (spriteData.x > 0)
			spriteData.x -= frameTime * ASSIST_TANK_MOVEMENT_SPEED;
		else
			isMovingRight = true;
	}

}