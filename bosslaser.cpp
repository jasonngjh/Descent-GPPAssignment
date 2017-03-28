#include "bosslaser.h"
//=============================================================================
// default constructor
//=============================================================================
BossLaser::BossLaser() : Entity()
{
	spriteData.width = BossLaserNS::WIDTH;           // size of Ship1
	spriteData.height = BossLaserNS::HEIGHT;
	spriteData.x = BossLaserNS::X;                   // location on screen
	spriteData.y = BossLaserNS::Y;
	spriteData.rect.bottom = BossLaserNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = BossLaserNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = BossLaserNS::ANIMATION_DELAY;
	startFrame = BossLaserNS::START_FRAME;     // first frame of ship animation
	endFrame = BossLaserNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = BossLaserNS::WIDTH / 2.0;
	mass = BossLaserNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool BossLaser::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void BossLaser::draw()
{
	Image::draw();              // draw ship

	

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void BossLaser::update(float frameTime)
{
	//http://jsfiddle.net/LyM87/ cannonball physics
	//if thrown
	Entity::update(frameTime);
	velocity.x = (float)(sin(degree*RADTODEGREE)*BOSSLASER_BASE_SPEED);
	velocity.y = (float)(cos(degree*RADTODEGREE)*BOSSLASER_BASE_SPEED);
	spriteData.x += velocity.x*frameTime;
	spriteData.y += velocity.y*frameTime;
	setFrames(startFrame, endFrame);
	setCurrentFrame(startFrame);
	setFrameDelay(frameDelay);
//	spriteData.x += velocity.x;
//	spriteData.y += velocity.y;
	
	



	//crosshair.setCurrentFrame(ShellNS::CROSSHAIR_START_FRAME);
	//Entity::update(frameTime);


}


