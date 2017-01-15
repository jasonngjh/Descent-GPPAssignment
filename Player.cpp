#include "Player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
	spriteData.width = PlayerNS::WIDTH;           // size of Ship1
	spriteData.height = PlayerNS::HEIGHT;
	spriteData.x = PlayerNS::X;                   // location on screen
	spriteData.y = PlayerNS::Y;
	spriteData.rect.bottom = PlayerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PlayerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = PlayerNS::ANIMATION_DELAY;
	startFrame = PlayerNS::START_FRAME;     // first frame of ship animation
	endFrame = PlayerNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = PlayerNS::WIDTH / 2.0;
	mass = PlayerNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	maxHealth = PLAYER_MAX_HEALTH;
	baseStrength = PLAYER_BASE_STRENGTH;

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	
}

//additional methods here
