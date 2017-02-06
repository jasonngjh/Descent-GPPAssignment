#include "Spaceship_bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Spaceship_bullet::Spaceship_bullet() : Entity()
{
	spriteData.width = Spaceship_bullet_NS::WIDTH;           // size of Ship1
	spriteData.height = Spaceship_bullet_NS::HEIGHT;
	spriteData.x = Spaceship_bullet_NS::X;                   // location on screen
	spriteData.y = Spaceship_bullet_NS::Y;
	spriteData.rect.bottom = Spaceship_bullet_NS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Spaceship_bullet_NS::WIDTH;
	frameDelay = Spaceship_bullet_NS::ANIMATION_DELAY;
	startFrame = Spaceship_bullet_NS::START_FRAME;     // first frame of ship animation
	endFrame = Spaceship_bullet_NS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Spaceship_bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Spaceship_bullet::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Spaceship_bullet::update(float frameTime)
{

}