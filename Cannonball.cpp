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
	forcePower = 0;

	Image::setScale(0.5);
	Image::setVisible(false);
	setActive(false);

	chargingTexture = new TextureManager();
	chargingBar = new Image();
}

//=============================================================================
// destructor
//=============================================================================
Cannonball::~Cannonball()
{
	delete chargingBar;
	delete chargingTexture;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Cannonball::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	if (!chargingTexture->initialize(gamePtr->getGraphics(), CHARGINGBAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing charging bar texture"));

	if (!chargingBar->initialize(gamePtr->getGraphics(), CHARGINGBAR_WIDTH, CHARGINGBAR_HEIGHT, CHARGINGBAR_TEXTURE_COLUMNS, chargingTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing charging bar"));
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Cannonball::draw()
{
	chargingBar->draw();
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Cannonball::update(float frameTime)
{

	if (!getActive() && (velocity.x == 0 && velocity.y == 0))
	{
		//onGround = true;
		visible = false;
		boolKeyHold = false;
		isCharging = false;
	}

	if (onGround || !(getActive())){
		if (input->isKeyDown(SPACE_KEY))
		{
			std::cout << "position x y " << getX() << "/" << getY() << "is visible, active? " << visible << ", " << active << std::endl;
			std::cout << "velocity x\y : " << velocity.x << "/" << velocity.y << std::endl;
			boolKeyHold = true;
		}
		else
		{
			boolKeyHold = false;
		}
	}


	if (boolKeyHold && !getActive())
	{
		if (!isCharging)
			std::async(&Cannonball::checkForHold, this);
	}


	if (getActive())
	{
		if ((spriteData.y > GROUND_LEVEL_HEIGHT))
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


}
void Cannonball::hit(hitWho target)
{
	if (target == land)
	{
		onGround = true;
		setActive(false);
		//Image::setVisible(false);
		spriteData.y = GROUND;//change value to where ur land is changes
		velocity.y = 0.0;
		velocity.x = 0.0;
	}
	if (target == spaceShip)
	{
		onGround = true;
		setActive(false);
	}
	if (target == bossShip)
	{
		forcePower = 0;
		setActive(false);
		onGround = true;
	}
	if (target == player)
	{
		setActive(false);
		onGround = true;
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
void Cannonball::playerCannonball()
{
	float initialVelocity = 2000.0;

	onGround = false;
	setActive(true);
	Image::setVisible(true);
	D3DXVECTOR2 v;
	int ang = tank->getTankAngle();
	switch (ang)
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
		std::cout << "tank angle 20" << std::endl;
		velocity.y = -(sin((ADAPTCIRCLE - ang + FIXANGLE) * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos((ADAPTCIRCLE - ang + FIXANGLE)  * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		std::cout << velocity.x << "," << std::endl;
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
		std::cout << "tank angle 40" << std::endl;
		velocity.y = -(sin((ADAPTCIRCLE - ang + FIXANGLE) * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos((ADAPTCIRCLE - ang + FIXANGLE) * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
		std::cout << "tank angle 60" << std::endl;
		velocity.y = -(sin((ADAPTCIRCLE - ang + FIXANGLE) * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos((ADAPTCIRCLE - ang + FIXANGLE) * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
		std::cout << "tank angle 90" << std::endl;
		velocity.y = -(sin(ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos(ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
		std::cout << "tank angle 120" << std::endl;
		velocity.y = -(sin(ADAPTCIRCLE - ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos(ADAPTCIRCLE - ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
		std::cout << "tank angle 140" << std::endl;
		velocity.y = -(sin(ADAPTCIRCLE - ang* RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos(ADAPTCIRCLE - ang* RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
		std::cout << "tank angle ADAPTCIRCLE" << std::endl;
		velocity.y = -(sin(ADAPTCIRCLE - ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
		velocity.x = -(cos(ADAPTCIRCLE - ang * RADTODEGREE)*CANNONBALL_BASE_SPEED*speedMultiplier);
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
	std::cout << " is charging cannon " << std::endl;	//remove before 2nd submission

	if (currentChargeTime > 0 && currentChargeTime <= 0.5)
	chargingBar->setCurrentFrame(5);
	if (currentChargeTime > 0.5 && currentChargeTime <= 1.0)
	chargingBar->setCurrentFrame(4);
	if (currentChargeTime > 1.0 && currentChargeTime <= 1.5)
	chargingBar->setCurrentFrame(3);
	if (currentChargeTime > 1.5 && currentChargeTime <= 2.0)
	chargingBar->setCurrentFrame(2);
	if (currentChargeTime > 2.0 && currentChargeTime <= 2.5)
	chargingBar->setCurrentFrame(1);
	if (currentChargeTime > 2.5 && currentChargeTime <= 3.0)
	chargingBar->setCurrentFrame(0);

	if (currentChargeTime > 3.0)
	{
	currentChargeTime = 3.0;
	boolKeyHold = false;
	}
	}
	chargingBar->setCurrentFrame(6);
	calulateForce(currentChargeTime);
	playerCannonball();
	currentChargeTime = 0.0;
	std::cout << "finished charging" << std::endl;
	isCharging = false;
	hasJustFired = true;		//for sound

	
}
//=============================================================================
// calculateForce(double)
// use the time to get the force
//=============================================================================
void Cannonball::calulateForce(double time)
{
	if (time >= 0.0 && time < 1.0)
	{
		setForcePower(10);
		speedMultiplier = 1.5;
	}
	if (time >= 1.0 && time < 2.0)
	{
		setForcePower(25);
		speedMultiplier = 2;
	}
	if (time >= 2.0 && time <= 3.0)
	{
		setForcePower(50);
		speedMultiplier = 2.75;
	}

}

//=============================================================================
// setForcePower()
// set the force power of the cannonball
//=============================================================================
void Cannonball::setForcePower(int f)
{
	forcePower = f;
	if (f = 0)
	{
		setVisible(false);
	}
}

//=============================================================================
// getForcePower()
// get the force power of the cannonball
//=============================================================================
int Cannonball::getForcePower()
{
	return forcePower;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Cannonball::resetAll()
{
	chargingTexture->onResetDevice();
	return;
}

//=============================================================================
// initialise charging bar
//=============================================================================
void Cannonball::initialiseChargingbar(float x, float y)
{
	chargingBar->setCurrentFrame(6);
	chargingBar->setScale(2);
	chargingBar->setX(x + 10.0f);
	chargingBar->setY(y + 90.0f);
}

//=============================================================================
// update charging bar as the tank is moving
//=============================================================================
void Cannonball::updateChargingBar(float frametime, float x)
{
	if ((input->isKeyDown(LEFT_KEY)) || (input->isKeyDown(RIGHT_KEY)))
	{
		chargingBar->setX(x + 10.0f);
	}
}