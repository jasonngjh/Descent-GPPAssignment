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
	health = BOSS_SPACESHIP_STARTING_HEALTH;
	hitRightCount = 0;
	isTop = true;
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
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;     // move ship along X 
	if (spriteData.x > GAME_WIDTH - Boss_SpaceshipNS::WIDTH*getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - Boss_SpaceshipNS::WIDTH*getScale();
		velocity.x = -velocity.x;               // reverse X direction
		hitRightCount++;
		std::cout << "Hit right " << hitRightCount << " times" << std::endl;
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		velocity.x = -velocity.x;               // reverse X direction
	}
	// if hit bottom screen edge
	if (spriteData.y > GAME_HEIGHT - Boss_SpaceshipNS::HEIGHT*getScale())
	{
		// position at bottom screen edge
		spriteData.y = GAME_HEIGHT - Boss_SpaceshipNS::HEIGHT*getScale();
		velocity.y = -velocity.y;               // reverse Y direction
	}
	else if (spriteData.y < 0)                  // else if hit top screen edge
	{
		spriteData.y = 0;                       // position at top screen edge
		velocity.y = -velocity.y;               // reverse Y direction
	}
	if (isTop&&hitRightCount==3)
	{
		spriteData.y = spriteData.y + 50;
		hitRightCount = 0; 
		isTop = false;
	}
	else if (!isTop&&hitRightCount == 3)
	{
		spriteData.y = spriteData.y - 50;
		hitRightCount = 0;
		isTop = true;
	}
}

//additional methods here
