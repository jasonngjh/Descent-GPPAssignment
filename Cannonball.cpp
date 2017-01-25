#include "Cannonball.h"

//=============================================================================
// default constructor
//=============================================================================
Cannonball::Cannonball() : Entity()
{
	spriteData.width = CannonballNS::WIDTH;           // size of Ship1
	spriteData.height = CannonballNS::HEIGHT;
	spriteData.x = CannonballNS::X;                   // location on screen
	spriteData.y = CannonballNS::Y;
	spriteData.rect.bottom = CannonballNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = CannonballNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = CannonballNS::ANIMATION_DELAY;
	startFrame = CannonballNS::START_FRAME;     // first frame of ship animation
	endFrame = CannonballNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = CannonballNS::WIDTH / 2.0;
	mass = CannonballNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Cannonball::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	damageLeft = CannonballNS::DAMAGE;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Cannonball::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Cannonball::update(float frameTime)
{
	//http://jsfiddle.net/LyM87/ cannonball physics
	//if thrown
	//spriteData.angle += frameTime * CannonballNS::ROTATION_RATE;
	velocity.y += GRAVITY*frameTime;
	spriteData.y += frameTime*velocity.y;
	spriteData.x += frameTime*velocity.x;

	if (input->isKeyDown(SPACE_KEY))
	{
		velocity.y = -500.0;
		velocity.x = 300.0;
	}
	


	if (spriteData.x > GAME_WIDTH - CannonballNS::WIDTH*getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - CannonballNS::WIDTH*getScale();
		velocity.x = -velocity.x;               // reverse X direction
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		velocity.x = -velocity.x;               // reverse X direction
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - CannonballNS::HEIGHT*getScale())
	{
		// position at bottom screen edge
		spriteData.y = GAME_HEIGHT - CannonballNS::HEIGHT*getScale();
		velocity.y = -velocity.y;               // reverse Y direction
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		spriteData.y = 0;                       // position at top screen edge
		velocity.y = -velocity.y;               // reverse Y direction
	}

	
}
int Cannonball::getDamageLeft(){ return damageLeft; }
void Cannonball::hit(hitWho target)
{
	if (target == land)
	{
		spriteData.y = GAME_HEIGHT - 50;//change value to where ur land is changes
		velocity.y = 0.0;
		velocity.x = 0.0;

	}
	if (target == spaceShip)
	{
		if (damageLeft>0)
		damageLeft -= 1;
		else damageLeft = 0;
	}
	if (target == bossShip)
	{
		if (damageLeft>0)
			damageLeft -= 1;
		else damageLeft = 0;
		
	}
}
//additional methods here
