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
	speed = 100.0f;
	tankAngle = 90;
	tankDirection = false;
	baseStrength = PLAYER_BASE_STRENGTH;
	health = PLAYER_MAX_HEALTH;
	
}

//=============================================================================
// Deconstructor
// 
//=============================================================================
Player::~Player()
{
	delete tankHealth;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	tankHealthTexture = new TextureManager();
	tankHealth = new Image();

	if (!tankHealthTexture->initialize(gamePtr->getGraphics(), TANK_HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank health texture"));

	if (!tankHealth->initialize(gamePtr->getGraphics(), PLAYER_HEALTH_WIDTH, PLAYER_HEALTH_HEIGHT, PLAYER_HEALTH_TEXTURE_COLUMNS, tankHealthTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank health"));

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
	tankHealth->draw();
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

	if (spriteData.x > GAME_WIDTH - PlayerNS::WIDTH*getScale())
	{
		// position at right screen edge
		spriteData.x = GAME_WIDTH - PlayerNS::WIDTH*getScale();
		if (velocity.x > 0)
			velocity.x = -velocity.x;               // reverse X direction
	}
	else if (spriteData.x < 0)                  // else if hit left screen edge
	{
		spriteData.x = 0;                       // position at left screen edge
		if (velocity.x < 0)
			velocity.x = -velocity.x;               // reverse X direction
	}

	if (input->isKeyDown(LEFT_KEY))
	{
		spriteData.flipHorizontal = false;
		tankDirection = false;
		spriteData.x -= frameTime * speed;
		tankHealth->setX(spriteData.x + 10.0f);
	}
	if (input->isKeyDown(RIGHT_KEY))
	{
		spriteData.flipHorizontal = true;
		tankDirection = true;
		spriteData.x += frameTime * speed;
		tankHealth->setX(spriteData.x+ 10.0f);
	}
	if (input->wasKeyPressed(UP_KEY))
	{
		switch (tankAngle){
		case 20:	tankAngle = 40;
			break;
		case 40:	tankAngle = 60;
			break;
		case 60:	tankAngle = 90;
			break;
		case 90:	tankAngle = 120;
			break;
		case 120:	tankAngle = 140;
			break;
		case 140:	tankAngle = 160;
			break;
		case 160: break;
		default: break;
		}
	}
	if (input->wasKeyPressed(DOWN_KEY))
	{
		switch (tankAngle){
		default: break;
		case 20: break;
		case 40:	tankAngle = 20;
			break;
		case 60:	tankAngle = 40;
			break;
		case 90:	tankAngle = 60;
			break;
		case 120:	tankAngle = 90;
			break;
		case 140:	tankAngle = 120;
			break;
		case 160:	tankAngle = 140;
			break;
		}
	}

	if (health < 0)
		health = 0;
	if (health > PLAYER_MAX_HEALTH)
		health = PLAYER_MAX_HEALTH;

	if (health < (0.1 * PLAYER_MAX_HEALTH)) //less than 10%
		tankHealth->setCurrentFrame(6);
	else if (health < (0.25 * PLAYER_MAX_HEALTH)) // less than 25%
		tankHealth->setCurrentFrame(5);
	else if (health < (0.5* PLAYER_MAX_HEALTH)) // less than 50%
		tankHealth->setCurrentFrame(4);
	else if (health < (0.6 * PLAYER_MAX_HEALTH)) // less than 60%
		tankHealth->setCurrentFrame(3);
	else if (health < (0.8 * PLAYER_MAX_HEALTH)) //less than 80%
		tankHealth->setCurrentFrame(2);
	else if (health < PLAYER_MAX_HEALTH) // less than 100%
		tankHealth->setCurrentFrame(1);
	else if (health == PLAYER_MAX_HEALTH) // 100%
		tankHealth->setCurrentFrame(0);
	else if (health == 0)
		tankHealth->setVisible(false); //GAMES END HERE

	tankHealth->update(frameTime);
}

//additional methods here

//=============================================================================
// setSpeed
// set the speed of the player
//=============================================================================
void Player::setSpeed(float s)
{
	speed = s;
}

//=============================================================================
// getSpeed
// get the speed of the player
//=============================================================================
float Player::getSpeed()
{
	return speed;
}

//=============================================================================
// setTankAngle
// set the speed of the player
//=============================================================================
void Player::setTankAngle(int a)
{
	tankAngle = a;
}

//=============================================================================
// getSpeed
// get the speed of the player
//=============================================================================
int Player::getTankAngle()
{
	return tankAngle;
}

//=============================================================================
// getDirection
// get the Direction of the player
//=============================================================================
bool Player::getTankDirection()
{
	return tankDirection;
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Player::releaseAll()
{
	tankHealthTexture->onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Player::resetAll()
{
	tankHealthTexture->onResetDevice();
	return;
}

//=============================================================================
// initialise healthbar of the tank
//=============================================================================
void Player::initialiseTankHealthbar()
{
	tankHealth->setCurrentFrame(0);
	tankHealth->setScale(2);
	tankHealth->setX(Player::spriteData.x + 10.0f);
	tankHealth->setY(Player::spriteData.y + 70.0f);
}

//=============================================================================
// setHealth
// set health
//=============================================================================
void Player::setHealth(double h)
{
	health = h;
}

//=============================================================================
// getHealth
// return health
//=============================================================================
double Player::getHealth()
{
	return health;
}