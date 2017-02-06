#include "powerup.h"
//=============================================================================
// default constructor
//=============================================================================
Powerup::Powerup() :Entity()
{
	spriteData.width = PowerupNS::WIDTH;           // size of Ship1
	spriteData.height = PowerupNS::HEIGHT;
	spriteData.x = PowerupNS::X;                   // location on screen
	spriteData.y = PowerupNS::Y;
	spriteData.rect.bottom = PowerupNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = PowerupNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = PowerupNS::ANIMATION_DELAY;
	startFrame = PowerupNS::START_FRAME;     // first frame of ship animation
	endFrame = PowerupNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = PowerupNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Powerup::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//health = SPACESHIP_STARTING_HEALTH;

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Powerup::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Powerup::update(float frameTime)
{
	Entity::update(frameTime);

	//rotate 
	//fall downwards if Y is less than ground level
	//if not, don't fall, just rotate

	spriteData.angle += frameTime * PowerupNS::ROTATION_RATE;  // rotates the powerup

	if (spriteData.y + POWERUP_HEIGHT < GROUND_LEVEL_HEIGHT)
		spriteData.y += frameTime * POWERUP_MOVEMENT_SPEED;         // move powerup along Y

	
}

//=============================================================================
// start and runs timer thread
//=============================================================================
void Powerup::beginExpireCountdown()
{
	std::async(&Powerup::powerup_timer_start, this);
}

//=============================================================================
// timer function
// to track each individual powerup's expiry time
//	using thread
//=============================================================================
void Powerup::powerup_timer_start()
{
	//create timer

	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);	//saves the time that the thread started on

	std::cout << "Starting time: " << startingTime << std::endl;

	bool loop = true;
	while (loop)
	{

		//setSecondsPassed((clock() - timer) / (double)CLOCKS_PER_SEC);  //convert computer timer to real life seconds

		if ((fmod(getSecondsPassed(), SECOND) == 0))
		{
			//every second in processor, check and update real time
			time(&clockTimer);  //get and update current time
			seconds = difftime(clockTimer, startingTime);
		}
			
		if (seconds == POWERUP_START_BLINKING_TIME_MARK)
		{
			endFrame = POWERUP_BLINKING_END_FRAME;
		}

		else if (seconds == POWERUP_OBJECT_DURATION)
		{
			active = false;	//this triggers the kill command in Descent.cpp
			loop = false;	//stops the timer since powerup has expired
		}

	}
}