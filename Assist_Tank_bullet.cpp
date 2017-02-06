#include "Assist_Tank_bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Assist_Tank_bullet::Assist_Tank_bullet() : Entity()
{
	spriteData.width = Assist_Tank_bullet_NS::WIDTH;           // size of Ship1
	spriteData.height = Assist_Tank_bullet_NS::HEIGHT;
	spriteData.x = Assist_Tank_bullet_NS::X;                   // location on screen
	spriteData.y = Assist_Tank_bullet_NS::Y;
	spriteData.rect.bottom = Assist_Tank_bullet_NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Assist_Tank_bullet_NS::WIDTH;
	frameDelay = Assist_Tank_bullet_NS::ANIMATION_DELAY;
	startFrame = Assist_Tank_bullet_NS::START_FRAME;     // first frame of ship animation
	endFrame = Assist_Tank_bullet_NS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Assist_Tank_bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Assist_Tank_bullet::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Assist_Tank_bullet::update(float frameTime)
{

	if (active)
	{

		Entity::update(frameTime);
		//moves the tank left and right
		spriteData.y -= frameTime*ASSIST_TANK_BULLET_SPEED;	//flies up
	}

}