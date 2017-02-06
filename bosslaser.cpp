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
void BossLaser::update(float frameTime, Player turret)
{
	//http://jsfiddle.net/LyM87/ cannonball physics
	//if thrown
	//spriteData.angle += frameTime * ShellNS::ROTATION_RATE;

	//distance = sqrt(pow(turret.getX() - spriteData.x, 2) + pow(turret.getY() - spriteData.y, 2));
	spriteData.x += velocity.x;
	spriteData.y += velocity.y;
	if (spriteData.x > GAME_WIDTH - BossLaserNS::WIDTH*getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - BossLaserNS::WIDTH*getScale();
		velocity.x = -velocity.x;               // reverse X direction
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		velocity.x = -velocity.x;               // reverse X direction
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - BossLaserNS::HEIGHT*getScale())
	{
		// position at bottom screen edge
		spriteData.y = GAME_HEIGHT - BossLaserNS::HEIGHT*getScale();
		velocity.y = -velocity.y;               // reverse Y direction
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		spriteData.y = 0;                       // position at top screen edge
		velocity.y = -velocity.y;               // reverse Y direction
	}
	//crosshair.setCurrentFrame(ShellNS::CROSSHAIR_START_FRAME);
	//Entity::update(frameTime);


}

