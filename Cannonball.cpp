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
	onGround = true;
	timeHold = 1.0;
	time = 5;

	Image::setScale(0.5);
	//Image::setVisible(false);
}

//=============================================================================
// destructor
//=============================================================================
Cannonball::~Cannonball()
{
	SAFE_DELETE(tank);
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
	if (onGround){
		//if player one
		if (input->isKeyDown(SPACE_KEY))
		{
			boolKeyHold = true;
		}
		else
		{
			boolKeyHold = false;
		}
	}
	
	if (boolKeyHold)
	{
		if (!isCharging)
		{
			std::async(&Cannonball::checkForHold, this);
		}
	}

	if (spriteData.y > GROUND)
	{
		hit(land);
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

	//if thrown
	velocity.y += GRAVITY*frameTime;
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}
void Cannonball::hit(hitWho target)
{
	if (target == land)
	{
		onGround = true;
		//Image::setVisible(false);
		spriteData.y = GROUND;//change value to where ur land is changes
		velocity.y = 0.0;
		velocity.x = 0.0;
		damageLeft = 5;
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

//=============================================================================
// setTankAngle
// set the tank angle
//=============================================================================
void Cannonball::getTank(Player* t)
{
	tank = t;
}

//=============================================================================
// playerCannonball()
// encapsulate the method to for firing the ball based on which player
//=============================================================================
void Cannonball::playerCannonball(double time)
{
	std::cout << "time: " << time << std::endl;

	float initialVelocity;
	if (time > 0 && time <= 1)
	{
		initialVelocity = 2000.0;
	}
	onGround = false;
	Image::setVisible(true);
	D3DXVECTOR2 v;
	switch (tank->getTankAngle())
	{

	case 20:
		if (tank->getTankDirection()){ // if facing right of screen
			spriteData.x = tank->getX() + 55.0f;
			spriteData.y = tank->getY() - 15.0f;
		}
		else{ //else face left
			spriteData.x = tank->getX() + 63.0f;
			spriteData.y = tank->getY() - 15.0f;
		}
		velocity.x = initialVelocity * (float)cos(0.349066);
		velocity.y = initialVelocity * (float)sin(0.349066) * GRAVITY;
		Entity::setVelocity
		std::cout << velocity.x << std::endl;
		std::cout << velocity.y << std::endl;
		break;
	case 40:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 55.0f;
			spriteData.y = tank->getY() - 23.0f;
		}
		else{
			spriteData.x = tank->getX() + 63.0f;
			spriteData.y = tank->getY() - 23.0f;
		}
		velocity.y = -200.0;
		velocity.x = 200.0f;
		break;
	case 60:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 45.0f;
			spriteData.y = tank->getY() - 31.0f;
		}
		else{
			spriteData.x = tank->getX() + 55.0f;
			spriteData.y = tank->getY() - 31.0f;
		}
		velocity.y = -300.0;
		velocity.x = 200.0f;
		break;

	case 90:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 27.0f;
			spriteData.y = tank->getY() - 33.0f;
		}
		else{
			spriteData.x = tank->getX() + 37.0f;
			spriteData.y = tank->getY() - 33.0f;
		}
		velocity.y = -400.0;
		velocity.x = 0.0;
		break;

	case 120:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 12.0f;
			spriteData.y = tank->getY() - 31.0f;
		}
		else{
			spriteData.x = tank->getX() + 21.0f;
			spriteData.y = tank->getY() - 31.0f;
		}
		velocity.y = -300.0;
		velocity.x = -200.0f;
		break;
	case 140:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 7.0f;
			spriteData.y = tank->getY() - 23.0f;
		}
		else{
			spriteData.x = tank->getX() + 17.0f;
			spriteData.y = tank->getY() - 23.0f;
		}
		velocity.y = -200.0;
		velocity.x = -200.0f;
		break;
	case 160:
		if (tank->getTankDirection()){
			spriteData.x = tank->getX() + 0.0f;
			spriteData.y = tank->getY() - 15.0f;
		}
		else{
			spriteData.x = tank->getX() + 14.0f;
			spriteData.y = tank->getY() - 15.0f;
		}
		velocity.y = -100.0;
		velocity.x = -200.0;
		break;
		}
}

//=============================================================================
// checkForHold()
// calculate how long the player has been holding the fire key
//=============================================================================
void Cannonball::checkForHold()
{
	isCharging = true;
	double currentChargeTime = 0.0;
	clock_t timer = clock();//start timer
	while (boolKeyHold)
	{
		currentChargeTime = ((clock() - timer) / (double)CLOCKS_PER_SEC);  //convert computer timer to real life seconds

		if (currentChargeTime > 3.0)
		{
			currentChargeTime = 3.0;
			boolKeyHold = false;
		}
	}
	
	playerCannonball(currentChargeTime);
	currentChargeTime = 0.0;
	boolKeyHold = false;
	isCharging = false;
}